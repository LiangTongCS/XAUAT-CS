package com.airesume.utils;

import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.text.PDFTextStripper;
import org.apache.poi.xwpf.extractor.XWPFWordExtractor;
import org.apache.poi.xwpf.usermodel.XWPFDocument;
import org.springframework.web.multipart.MultipartFile;
import java.io.InputStream;

public class FileUtils {

    public static String readFileContent(MultipartFile file) throws Exception {
        String fileName = file.getOriginalFilename();
        String content = "";
        
        try (InputStream inputStream = file.getInputStream()) {
            if (fileName.endsWith(".pdf")) {
                PDDocument document = PDDocument.load(inputStream);
                PDFTextStripper stripper = new PDFTextStripper();
                content = stripper.getText(document);
                document.close();
            } else if (fileName.endsWith(".docx")) {
                XWPFDocument docx = new XWPFDocument(inputStream);
                XWPFWordExtractor extractor = new XWPFWordExtractor(docx);
                content = extractor.getText();
                extractor.close();
            } else {
                throw new Exception("不支持的文件格式");
            }
        }
        return content;
    }
}