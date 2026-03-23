// 全局变量存储会话ID
let sessionId = null;
// 全局变量
let currentSessionId = null;
let historySessions = [];
let isSidebarVisible = true;

// 在script.js中添加全局请求方法
async function fetchWithAuth(url, options = {}) {
    //特殊处理OPTIONS请求，不需要加'Authorization'头
    /*
这样处理的好处：
    1.保持预检请求的纯净性：
    OPTIONS 请求不添加任何认证头部
    让预检请求只关注 CORS 策略检查

    2.遵循浏览器安全机制：
    浏览器自动处理预检请求流程
    我们不需要在应用层干预这个过程

    3.确保实际请求正常发送：
    只有预检成功后，浏览器才会发送实际请求
    实际请求会正常添加 Authorization 头
    */
    if (options.method && options.method.toUpperCase() === 'OPTIONS') {
        return fetch(url, options);
    }
    // 从localStorage获取token
    const token = localStorage.getItem('token');
    if (!token) {
        // 如果没有token，跳转到登录页
        window.location.href = 'login.html';
        return;
    }

    // 设置Authorization头，返回带token的请求
    options.headers = options.headers || {};
    options.headers['Authorization'] = `Bearer ${token}`;

    const response = await fetch(url, options);

    // 如果返回401未授权，跳转到登录页
    if (response.status === 401) {
        localStorage.removeItem('token');
        window.location.href = 'login.html';
        return;
    } else if (response.status === 403) {
        alert("您没有权限使用此功能！");
        return;
    }

    return response;
}

async function sendMessage() {
    const input = document.getElementById('messageInput');
    const message = input.value.trim();

    if (!message) return;

    // 显示用户消息
    addMessage(message, 'user');
    input.value = '';

    // 禁用发送按钮
    setSendButtonState(true);

    // 显示加载指示器
    const loadingIndicator = showLoadingIndicator("AI正在思考中...");

    try {
        const response = await fetchWithAuth('http://localhost:8080/chat', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                sessionId: currentSessionId,
                message: message
            })
        });

        // 如果未授权已处理
        if (!response) {
            removeLoadingIndicator();
            setSendButtonState(false);
            return;
        }

        const result = await response.json();

        // 移除加载指示器
        removeLoadingIndicator();

        // 保存会话ID
        if (!currentSessionId) currentSessionId = result.sessionId;

        // 显示AI回复
        addMessage(result.response, 'ai');


        // // 显示分析结果（带打字效果），失去markdown格式整理功能
        // const chatMessages = document.getElementById('chatMessages');
        // const messageDiv = document.createElement('div');
        // messageDiv.className = 'message ai-message';
        //
        // const contentContainer = document.createElement('div');
        // contentContainer.className = 'typing-animation';
        // messageDiv.appendChild(contentContainer);
        //
        // chatMessages.appendChild(messageDiv);
        // chatMessages.scrollTop = chatMessages.scrollHeight;
        //
        // // 模拟打字效果
        // typeMessage(result.response, contentContainer, 10); // 更快的打字速度

        // 刷新历史对话列表
        fetchHistory();

    } catch (error) {
        removeLoadingIndicator();
        addMessage('对话失败，请重试', 'ai');
        console.error('Error:', error);
    } finally {
        // 启用发送按钮
        setSendButtonState(false);
    }
}

async function uploadResume() {
    const fileInput = document.getElementById('resumeUpload');
    const file = fileInput.files[0];

    if (!file) {
        alert('请选择简历文件');
        return;
    }

    // 显示用户消息
    addMessage(`已上传简历: ${file.name}`, 'user');
    // 禁用上传按钮
    setSendButtonState(true);
    // 显示加载指示器
    const loadingIndicator = showLoadingIndicator("正在分析简历内容...");

    const formData = new FormData();
    formData.append('resume', file);

    try {
        const response = await fetchWithAuth('http://localhost:8080/analyze', {
            method: 'POST',
            body: formData
        });

        if (!response) {
            removeLoadingIndicator();// 移除加载指示器
            setSendButtonState(false);// 启用上传按钮
            return;
        }

        const result = await response.json();
        console.log("后端返回数据:", result);

        // 保存会话ID
        currentSessionId = result.sessionId;
        // 移除加载指示器
        removeLoadingIndicator();

        // 显示状态消息
        showStatusMessage("简历分析完成", "success");

        // 解析 content 字段（它是一个 JSON 字符串）
        let resumeData = {};
        try {
            resumeData = JSON.parse(result.content);
        } catch (e) {
            console.error('解析 content 失败:', e);
        }
        console.log("解析后的简历数据:", resumeData);

        // 生成 Markdown 格式的分析结果
        const analysisResult = generateMarkdownAnalysis(resumeData);
        console.log("Markdown格式的分析结果:", analysisResult);
        // 显示分析结果
        addMessage(analysisResult, 'ai');
        // 刷新历史对话列表
        fetchHistory();

    } catch (error) {
        removeLoadingIndicator();
        addMessage("简历分析失败，请重试", 'ai');
        console.error('Error:', error);
    } finally {
        // 启用发送按钮
        setSendButtonState(false);
    }
}

// 生成Markdown分析报告
function generateMarkdownAnalysis(resumeData) {
    return `
## 简历分析报告

### 基本信息
- **姓名**: ${resumeData.name || '未提供'}
- **联系方式**: ${formatContact(resumeData.contact)}

### 教育经历
${formatEducation(resumeData.education)}

### 工作经历
${formatWorkExperience(resumeData.workExperience)}

### 技能
${formatSkills(resumeData.skills)}

### 简历评分
**${resumeData.qualityScore || '无'} / 10**

### 改进建议
${formatSuggestions(resumeData.improvementSuggestions)}
`;
}

// 格式化联系方式
function formatContact(contact) {
    if (!contact) return '未提供';

    if (typeof contact === 'string') {
        return contact;
    }

    let contactInfo = [];
    for (const [key, value] of Object.entries(contact)) {
        if (value) {
            contactInfo.push(`${key}: ${value}`);
        }
    }

    return contactInfo.length > 0 ? contactInfo.join(' | ') : '未提供';
}

// 格式化教育经历
function formatEducation(education) {
    if (!education) return '未提供';

    // 处理单对象或数组
    const eduList = Array.isArray(education) ? education : [education];

    if (eduList.length === 0) return '未提供';

    return eduList.map(edu => {
        let info = `- **${edu.school || '未知学校'}**`;
        if (edu.period) info += ` (${edu.period})`;
        if (edu.major) info += ` - ${edu.major}`;
        if (edu.degree) info += ` - ${edu.degree}`;
        if (edu.courses) info += `\n  - 相关课程: ${edu.courses}`;
        return info;
    }).join('\n');
}

// 格式化工作经历
function formatWorkExperience(workExperience) {
    if (!workExperience) return '未提供';

    // 处理单对象或数组
    const workList = Array.isArray(workExperience) ? workExperience : [workExperience];

    if (workList.length === 0) return '未提供';

    return workList.map(work => {
        let info = `- **${work.company || work.position || '未知职位'}**`;
        if (work.period) info += ` (${work.period})`;
        if (work.position && work.company) info += ` - ${work.position}`;
        if (work.description) info += `\n  - ${work.description}`;
        return info;
    }).join('\n');
}

// 格式化技能
function formatSkills(skills) {
    if (!skills) return '未提供';

    // 处理数组格式的技能
    if (Array.isArray(skills)) {
        return skills.map(skill => `- ${skill}`).join('\n');
    }

    // 处理对象格式的技能
    let skillSections = [];
    for (const [category, items] of Object.entries(skills)) {
        if (items && items.length > 0) {
            let categoryName = '';
            switch (category) {
                case 'technical':
                    categoryName = '技术技能';
                    break;
                case 'backend':
                    categoryName = '后端技能';
                    break;
                case 'frontend':
                    categoryName = '前端技能';
                    break;
                case 'tools':
                    categoryName = '开发工具';
                    break;
                case 'languages':
                    categoryName = '语言能力';
                    break;
                case 'certificates':
                    categoryName = '证书荣誉';
                    break;
                case 'softSkills':
                    categoryName = '软技能';
                    break;
                default:
                    categoryName = category;
            }

            skillSections.push(`**${categoryName}**:\n${items.map(item => `  - ${item}`).join('\n')}`);
        }
    }

    return skillSections.join('\n\n');
}

// 格式化改进建议
function formatSuggestions(suggestions) {
    if (!suggestions) return '无';

    if (typeof suggestions === 'string') {
        return suggestions;
    }

    if (Array.isArray(suggestions)) {
        return suggestions.map(s => `- ${s}`).join('\n');
    }

    return '无';
}

// 渲染Markdown为HTML
function renderMarkdown(markdown) {
    // 简单的Markdown到HTML转换
    return markdown
        .replace(/^### (.*$)/gim, '<h3>$1</h3>')
        .replace(/^## (.*$)/gim, '<h2>$1</h2>')
        .replace(/^- (.*$)/gim, '<li>$1</li>')
        .replace(/\*\*(.*?)\*\*/gim, '<strong>$1</strong>')
        .replace(/\n/g, '<br>');
}

// 配置 marked.js
marked.setOptions({
    breaks: true, // 自动换行
    gfm: true,    // 支持 GitHub Flavored Markdown
    highlight: function (code, lang) {
        const language = hljs.getLanguage(lang) ? lang : 'plaintext';
        return hljs.highlight(code, {language}).value;
    }
});

// 配置 MathJax（如果需要）
if (window.MathJax) {
    window.MathJax = {
        tex: {
            inlineMath: [['$', '$'], ['\\(', '\\)']]
        },
        options: {
            skipHtmlTags: ['script', 'noscript', 'style', 'textarea', 'pre'],
            ignoreHtmlClass: 'tex2jax_ignore'
        }
    };
}

//Markdown 渲染函数
function renderMarkdown(markdown) {
    // 将 Markdown 转换为 HTML
    const html = marked.parse(markdown);

    // 创建容器元素
    const container = document.createElement('div');
    container.className = 'markdown-body';
    container.innerHTML = html;

    // 渲染后处理
    setTimeout(() => {
        // 高亮所有代码块
        container.querySelectorAll('pre code').forEach((block) => {
            hljs.highlightElement(block);
        });

        // 渲染数学公式（如果使用 MathJax）
        if (window.MathJax) {
            MathJax.typesetPromise([container]);
        }
    }, 0);

    return container;
}

// 显示消息
// 显示消息
function addMessage(content, sender) {
    const chatMessages = document.getElementById('chatMessages');
    const messageDiv = document.createElement('div');
    messageDiv.className = `message ${sender}-message`;

    // 如果是 AI 消息
    if (sender === 'user') {
        messageDiv.innerHTML = content;
    }
    // 用户消息
    else {
        // 简历分析结果
        if (typeof content === 'string' && content.includes('## 简历分析结果')) {
            const markdownContainer = renderMarkdown(content);
            messageDiv.appendChild(markdownContainer);
        }
        // 普通 AI 消息
        else if (typeof content === 'string' && content.trim().length > 0) {
            const markdownContainer = renderMarkdown(content);
            messageDiv.appendChild(markdownContainer);
        }
        // 其他类型内容
        else {
            messageDiv.innerHTML = content;
        }

    }

    chatMessages.appendChild(messageDiv);
    chatMessages.scrollTop = chatMessages.scrollHeight;
}

////////////////////////////////////////
//退出登录
function logout() {
    // 调用后端退出接口
    fetchWithAuth('http://localhost:8080/logout', {
        method: 'POST',
        headers: {  // 添加内容类型声明
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            sessionId: currentSessionId
        })
    }).then(() => {
        // 清除本地存储的token
        localStorage.removeItem('token');
        // 清除会话ID
        currentSessionId = null;
        alert("您已退出登录！");
        // 跳转到登录页
        window.location.href = 'login.html';

    }).catch(error => {
        console.error('退出失败:', error);
        // 即使退出失败也清除本地token
        localStorage.removeItem('token');
        window.location.href = 'login.html';
    });

}

////////////////////////////////////////
// 设置AI服务
async function setAIService() {
    const service = document.getElementById('aiService').value;

    try {
        const response = await fetchWithAuth('http://localhost:8080/set-ai-service', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({service})
        });

        if (response.ok) {
            alert(`已切换到${service === 'wenxin' ? '文心一言' : 'DeepSeek'}服务`);
        } else {
            alert('切换服务失败');
        }
    } catch (error) {
        console.error('切换AI服务失败:', error);
        alert('切换服务失败');
    }
}

// 页面加载时获取当前AI服务
document.addEventListener('DOMContentLoaded', function () {
    // 默认选择DeepSeek
    document.getElementById('aiService').value = 'deepseek';

    // 可以添加从后端获取当前设置的逻辑
    // fetchCurrentAIService();
});

// 获取当前AI服务（可选）
async function fetchCurrentAIService() {
    try {
        const response = await fetchWithAuth('http://localhost:8080/get-ai-service');
        const service = await response.text();
        document.getElementById('aiService').value = service;
    } catch (error) {
        console.error('获取AI服务失败:', error);
    }
}

///////////////////////////////////////////////////
// 显示加载指示器
function showLoadingIndicator(message = "AI正在思考") {
    const chatMessages = document.getElementById('chatMessages');
    const loadingDiv = document.createElement('div');
    loadingDiv.className = 'loading-indicator';
    loadingDiv.id = 'loading-indicator';

    loadingDiv.innerHTML = `
        <div class="loading-dots">
            <div class="loading-dot"></div>
            <div class="loading-dot"></div>
            <div class="loading-dot"></div>
        </div>
        <div class="loading-text">${message}</div>
    `;

    chatMessages.appendChild(loadingDiv);
    chatMessages.scrollTop = chatMessages.scrollHeight;

    return loadingDiv;
}

// 显示状态消息
function showStatusMessage(message, type = 'info') {
    const chatMessages = document.getElementById('chatMessages');
    const statusDiv = document.createElement('div');
    statusDiv.className = `status-message ${type}`;
    statusDiv.textContent = message;

    chatMessages.appendChild(statusDiv);
    chatMessages.scrollTop = chatMessages.scrollHeight;

    // 5秒后自动消失
    setTimeout(() => {
        statusDiv.remove();
    }, 5000);

    return statusDiv;
}

// 移除加载指示器
function removeLoadingIndicator() {
    const loadingIndicator = document.getElementById('loading-indicator');
    if (loadingIndicator) {
        loadingIndicator.remove();
    }
}

// 模拟打字效果
function typeMessage(message, container, speed = 30) {
    let i = 0;
    container.innerHTML = '';

    function type() {
        if (i < message.length) {
            container.innerHTML += message.charAt(i);
            i++;
            setTimeout(type, speed);
        }
    }

    type();
}

// 禁用/启用发送按钮
function setSendButtonState(disabled) {
    const sendButton = document.querySelector('.chat-input button[onclick="sendMessage()"]');
    const uploadButton = document.querySelector('.chat-input button[onclick="uploadResume()"]');

    if (sendButton) sendButton.disabled = disabled;
    if (uploadButton) uploadButton.disabled = disabled;
}

/////////////////////////////////////////////////////
// 切换侧边栏显示/隐藏
function toggleSidebar() {
    const sidebar = document.getElementById('historySidebar');
    const toggleBtn = document.getElementById('toggleSidebar');

    isSidebarVisible = !isSidebarVisible;

    if (isSidebarVisible) {
        sidebar.classList.remove('hidden');
        sidebar.classList.add('visible');
        document.querySelector('.chat-container').style.marginLeft = '300px';
        toggleBtn.innerHTML = '<i class="fas fa-chevron-right"></i>';
    } else {
        sidebar.classList.remove('visible');
        sidebar.classList.add('hidden');
        document.querySelector('.chat-container').style.marginLeft = '0';
        toggleBtn.innerHTML = '<i class="fas fa-chevron-left"></i>';
    }
}

// 获取历史对话
async function fetchHistory() {
    try {
        const response = await fetchWithAuth('http://localhost:8080/history');
        if (!response) return;

        const history = await response.json();
        console.log("历史对话列表:", history);

        // 保存历史对话列表
        historySessions = history;
        renderHistoryList(history);
    } catch (error) {
        console.error('获取历史对话失败:', error);
    }
}

// 渲染历史对话列表
function renderHistoryList(history) {
    const historyList = document.getElementById('historyList');
    historyList.innerHTML = '';

    if (history.length === 0) {
        historyList.innerHTML = '<div class="no-history">暂无历史对话</div>';
        return;
    }

    history.forEach(session => {
        const item = document.createElement('div');
        item.className = 'history-item';
        if (session.sessionId === currentSessionId) {
            item.classList.add('active');
        }

        item.dataset.sessionId = session.sessionId;

        // 格式化时间
        const date = new Date(session.startTime);
        const timeString = date.toLocaleString();

        // 提取简历名称（如果存在）
        let resumeName = "普通对话";
        try {
            if (session.resumeName) {
                resumeName = session.resumeName;
            }
        } catch (e) {
            console.error('解析简历结果失败', e);
        }

        item.innerHTML = `
            <div class="history-title">
                <span>${resumeName}</span>
                <span class="session-id">${session.sessionId.substring(0, 8)}</span>
            </div>
            <div class="history-time">${timeString}</div>
        `;

        item.addEventListener('click', () => {
            loadSession(session.sessionId);
        });

        historyList.appendChild(item);
    });
}

// 搜索历史对话
function searchHistory() {
    const query = document.getElementById('historySearch').value.toLowerCase();

    if (!query) {
        renderHistoryList(historySessions);
        return;
    }

    const filtered = historySessions.filter(session => {
        // 尝试解析简历名称
        let resumeName = session.resumeName;

        return resumeName.toLowerCase().includes(query) ||
            session.sessionId.toLowerCase().includes(query);
    });

    renderHistoryList(filtered);
}

// 加载会话
async function loadSession(sessionId) {
    try {
        // 显示加载指示器
        showLoadingIndicator("正在加载会话...");

        const response = await fetchWithAuth(`http://localhost:8080/session/${sessionId}`);
        if (!response) return;

        const session = await response.json();
        console.log("会话内容:", session)

        // 更新当前会话ID
        currentSessionId = session.sessionId;

        // 清除当前聊天消息
        const chatMessages = document.getElementById('chatMessages');
        chatMessages.innerHTML = '';

        if (session.resumeResult) {
            let resumeData = {};
            // 渲染简历分析结果
            resumeData = JSON.parse(session.resumeResult);

            console.log("解析后的简历数据:", resumeData);

            // 生成 Markdown 格式的分析结果
            const analysisResult = generateMarkdownAnalysis(resumeData);
            console.log("Markdown格式的分析结果:", analysisResult);
            // 显示分析结果
            addMessage(analysisResult, 'ai');
        }
        // 渲染会话内容
        session.contentList.forEach(content => {
            addMessage(content.content, content.role);
        });

        // 高亮当前会话项
        document.querySelectorAll('.history-item').forEach(item => {
            item.classList.remove('active');
            if (item.dataset.sessionId === sessionId) {
                item.classList.add('active');
            }
        });

        // 移除加载指示器
        removeLoadingIndicator();

    } catch (error) {
        removeLoadingIndicator();
        showStatusMessage("加载会话失败", "error");
        console.error('加载会话失败:', error);
    }
}