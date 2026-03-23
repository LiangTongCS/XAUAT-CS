package com.airesume.interceptor;

import com.airesume.annotation.RequirePermission;
import com.airesume.utils.JwtUtils;
import com.airesume.utils.TokenContext;
import io.jsonwebtoken.Claims;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.extern.slf4j.Slf4j;
import org.springframework.core.annotation.Order;
import org.springframework.stereotype.Component;
import org.springframework.web.method.HandlerMethod;
import org.springframework.web.servlet.HandlerInterceptor;

@Order(1)
@Component
@Slf4j
public class LoginInterceptor implements HandlerInterceptor {
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        log.info("执行拦截");
        String URI = request.getRequestURI();

        System.setProperty("ai.service", "deepseek");
        log.info("请求URI：" + URI);

        // 放行OPTIONS预检请求
//        为什么需要处理 OPTIONS 请求？
//        1.预检请求机制：
//        当浏览器发送某些类型的跨域请求时，会先发送一个 OPTIONS 请求作为"预检"
//        这个预检请求的目的是确认服务器是否允许实际请求
//        浏览器自动处理这个过程，开发者不需要手动发送 OPTIONS 请求
//
//        2.认证头部的特殊性：
//        当请求包含自定义头部（如 Authorization）时，浏览器会触发预检
//                预检请求本身不包含认证信息
//        如果我们在预检请求中强制添加 Authorization 头，会导致预检失败
//
//        3.避免双重认证：
//        预检请求不需要认证，只需要检查 CORS 策略
//        如果我们在预检请求中添加认证头，会导致：
//        服务器尝试验证一个不存在的 token
//        预检请求被拒绝（401 未授权）
        if ("OPTIONS".equalsIgnoreCase(request.getMethod())) {
            return true;
        }

        if (URI.contains("/login")||URI.contains("/register")) {
            log.info("登录/注册页面，放行");
            return true;
        }
        if (URI.contains("/logout")) {
            //没有解析token，直接放行，所以后面日志打印当前用户为null
            log.info("退出登录页面，放行");
            return true;
        }

        // 从请求头获取token
        String token = request.getHeader("Authorization");
        if (token == null || !token.startsWith("Bearer ")) {
            log.info("请求头中没有token，拒绝访问");
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);//401
            return false;
        }

        token = token.substring(7); // 去掉"Bearer "
        try {
            Claims claims = JwtUtils.parseJWT(token);
            // 将用户信息存入request属性，方便后续使用
            //request.setAttribute("username", claims.get("username"));


            // 权限校验
            // 1. 检查是否为控制器方法
            if (!(handler instanceof HandlerMethod)) {
                return true;
            }

            HandlerMethod handlerMethod = (HandlerMethod) handler;

            // 从token中获取用户角色
            String role = claims.get("roles").toString();
            TokenContext.setCurrentUserRole(role);
            TokenContext.setCurrentUserName(claims.get("username").toString());

            // 2. 获取方法上的权限注解
            RequirePermission annotation = handlerMethod.getMethod().getAnnotation(RequirePermission.class);

            // 3. 无需权限的方法直接放行
            if (annotation == null) {
                return true;
            }
            // 4. 获取当前用户的角色


            log.info(",当前用户：" + claims.get("username") + ",当前用户角色：" + role);
            // 5.方法上的权限标识数组
            String[] roles = annotation.value();
            // 6.判断当前用户是否有权限访问
            for (String r : roles) {
                if (role.contains(r)) {
                    return true;
                }
            }
            response.setStatus(HttpServletResponse.SC_FORBIDDEN);
            return false;

        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            return false;
        }

    }

    @Override
    public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {
        // 清除ThreadLocal变量
        TokenContext.clear();
    }
}
