package com.airesume.service;

import com.airesume.pojo.Log;
import com.airesume.repository.LogRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class LogService {
    @Autowired
    private LogRepository logRepository;


    public void saveLog(Log log) {
        logRepository.save(log);
    }

    public void deleteLog(Integer logId) {
        logRepository.deleteById(logId);
    }

    public List<Log> getAllLog() {
        return logRepository.findAll();
    }

    //删除所有日志
    public void deleteAllLog() {
        logRepository.deleteAll();
    }
}
