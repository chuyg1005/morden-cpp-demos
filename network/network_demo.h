#ifndef CPP_LEARNING_DEMO_NETWORK_DEMO_H
#define CPP_LEARNING_DEMO_NETWORK_DEMO_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>

// 注意：实际的网络编程需要使用套接字API，这里提供概念性示例
// 在实际项目中，您可能需要包含 <sys/socket.h>, <netinet/in.h> 等

namespace network_demo {
    // 模拟TCP客户端
    class TCPClient {
    public:
        void connect(const std::string& host, int port) {
            std::cout << "连接到 " << host << ":" << port << std::endl;
            // 模拟连接过程
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "连接成功!" << std::endl;
        }
        
        void send(const std::string& message) {
            std::cout << "发送消息: " << message << std::endl;
        }
        
        std::string receive() {
            // 模拟接收消息
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            return "服务器响应: 消息已收到";
        }
        
        void disconnect() {
            std::cout << "断开连接" << std::endl;
        }
    };
    
    // 模拟TCP服务器
    class TCPServer {
    private:
        int port_;
        
    public:
        explicit TCPServer(int port) : port_(port) {}
        
        void start() {
            std::cout << "服务器启动，监听端口 " << port_ << std::endl;
        }
        
        void handle_client() {
            std::cout << "处理客户端连接..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "接收到来自客户端的消息" << std::endl;
            std::cout << "发送响应给客户端" << std::endl;
        }
        
        void stop() {
            std::cout << "服务器停止" << std::endl;
        }
    };
    
    // HTTP客户端模拟
    class HTTPClient {
    public:
        std::string get(const std::string& url) {
            std::cout << "发送GET请求到: " << url << std::endl;
            // 模拟网络延迟
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>欢迎!</h1></body></html>";
        }
        
        std::string post(const std::string& url, const std::string& data) {
            std::cout << "发送POST请求到: " << url << std::endl;
            std::cout << "数据: " << data << std::endl;
            // 模拟网络延迟
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return "HTTP/1.1 201 Created\nContent-Type: application/json\n\n{\"status\": \"success\"}";
        }
    };
    
    // URL解析器
    struct URL {
        std::string protocol;
        std::string host;
        int port;
        std::string path;
        
        static URL parse(const std::string& url_str) {
            URL url;
            // 简单的URL解析实现
            if (url_str.substr(0, 7) == "http://") {
                url.protocol = "http";
                std::string remaining = url_str.substr(7);
                size_t path_pos = remaining.find('/');
                if (path_pos != std::string::npos) {
                    url.host = remaining.substr(0, path_pos);
                    url.path = remaining.substr(path_pos);
                } else {
                    url.host = remaining;
                    url.path = "/";
                }
                url.port = 80;
            } else if (url_str.substr(0, 8) == "https://") {
                url.protocol = "https";
                std::string remaining = url_str.substr(8);
                size_t path_pos = remaining.find('/');
                if (path_pos != std::string::npos) {
                    url.host = remaining.substr(0, path_pos);
                    url.path = remaining.substr(path_pos);
                } else {
                    url.host = remaining;
                    url.path = "/";
                }
                url.port = 443;
            }
            return url;
        }
    };
    
    // TCP客户端演示
    void tcp_client_demo() {
        std::cout << "\n=== TCP客户端演示 ===" << std::endl;
        TCPClient client;
        client.connect("example.com", 8080);
        client.send("Hello, Server!");
        std::string response = client.receive();
        std::cout << "收到响应: " << response << std::endl;
        client.disconnect();
    }
    
    // TCP服务器演示
    void tcp_server_demo() {
        std::cout << "\n=== TCP服务器演示 ===" << std::endl;
        TCPServer server(8080);
        server.start();
        server.handle_client();
        server.stop();
    }
    
    // HTTP客户端演示
    void http_client_demo() {
        std::cout << "\n=== HTTP客户端演示 ===" << std::endl;
        HTTPClient client;
        
        // GET请求
        std::string response = client.get("http://example.com/index.html");
        std::cout << "GET响应:\n" << response << std::endl;
        
        // POST请求
        response = client.post("http://example.com/api/users", "{\"name\": \"张三\", \"age\": 30}");
        std::cout << "POST响应:\n" << response << std::endl;
    }
    
    // URL解析演示
    void url_parsing_demo() {
        std::cout << "\n=== URL解析演示 ===" << std::endl;
        std::string url_str = "https://www.example.com:443/api/users?id=123";
        URL url = URL::parse(url_str);
        std::cout << "协议: " << url.protocol << std::endl;
        std::cout << "主机: " << url.host << std::endl;
        std::cout << "端口: " << url.port << std::endl;
        std::cout << "路径: " << url.path << std::endl;
    }
    
    // 运行所有演示
    void run_demo() {
        std::cout << "=== 网络编程演示 ===" << std::endl;
        tcp_client_demo();
        tcp_server_demo();
        http_client_demo();
        url_parsing_demo();
    }
}

#endif //CPP_LEARNING_DEMO_NETWORK_DEMO_H