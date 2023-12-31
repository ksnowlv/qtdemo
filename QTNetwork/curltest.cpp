#include "curltest.h"

#include <curl/curl.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

using namespace rapidjson;
using namespace std;

CurlTest::CurlTest(QObject *parent)
    : QObject{parent}
{

}

// 回调函数，用于处理响应头
size_t header_callback(void *buffer, size_t size, size_t nmemb, void *userData) {
    // 计算存储数据的大小
    size_t real_size = size * nmemb;
    std::string* data = (std::string*)userData;

    // 将数据拼接到字符串中
    data->append(static_cast<char*>(buffer), real_size);
    cout<<data<<endl;
    return real_size;
}

// 回调函数，用于处理响应数据
size_t response_data_callback(void *buffer, size_t size, size_t nmemb, std::string *data) {
    // 计算存储数据的大小
    size_t real_size = size * nmemb;

    // 将数据拼接到字符串中
    data->append(static_cast<char*>(buffer), real_size);

    return real_size;
}

void CurlTest::handleCurlGetJsonParse(std::string& jsonData) {
    Document document;
    document.Parse(jsonData.c_str());

    // 检查解析是否成功
    if (document.HasParseError()) {
        std::cout << "解析JSON时出错" << std::endl;
    } else {
        // 从解析的JSON中提取数据
        if (document.IsObject()) {
            std::string message = document["message"].GetString();
            // int age = document["age"].GetInt();
            // std::string city = document["city"].GetString();

            // 输出解析结果
            std::cout << "message: " << message << std::endl;
        } else {
            std::cout << "无效的JSON格式" << std::endl;
        }
    }
}


void CurlTest::testCurlhttpGet() {

    CURL* curl = curl_easy_init();
    if (curl) {
        // 设置请求的 URL
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8081/user/home");
        // 设置写入响应头数据的目标
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        // curl_easy_setopt(curl, CURLOPT_HEADER, 1);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
        std::string responseHeader;
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &responseHeader);

        // 存储响应数据的字符串
        std::string responseData;

        // 设置写入响应数据的目标
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, response_data_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

        // 执行 HTTP 请求
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            long response_code;
            // 获取HTTP状态码
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            char *contentType = nullptr;
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &contentType);
            cout<<"response code:"<<response_code<<endl;
            cout<<"response header:"<<responseHeader<<endl;


            // 响应数据存储在 responseData 中，可以进行解析或处理
            cout << "Response received:" << responseData<<std::endl;
            handleCurlGetJsonParse(responseData);
        }

        // 清理 curl 资源
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize libcurl" << std::endl;
    }
}

/*
curl -X 'POST' \
    'http://127.0.0.1:8081/user/login' \
    -H 'accept: application/json' \
    -H 'Content-Type: application/json' \
    -d '{
  "name": "ksnowlv",
    "age": 0,
    "phone": "xxx",
              "verification_code": "123456"
}'
*/
void CurlTest::testCurlHttpPost() {
    // 创建一个JSON文档
    Document document;
    document.SetObject();
    Document::AllocatorType& allocator = document.GetAllocator();

    // 添加JSON字段
    document.AddMember("name", "ksnowlv", allocator);
    document.AddMember("age", 0, allocator);
    document.AddMember("phone", "15210795183", allocator);
    document.AddMember("verification_code", "123456", allocator);

    // 将JSON文档转换为字符串
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    std::string jsonStr = buffer.GetString();

    // 输出生成的JSON字符串
    std::cout << "生成的JSON字符串：" << jsonStr << std::endl;

    CURL* curl = curl_easy_init();
    if (curl) {
        // 设置请求的URL
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8081/user/login");

        // 设置请求头
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // 设置请求数据
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());

        // 设置请求为POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
        std::string responseHeader;
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &responseHeader);

        // 设置写入响应数据的目标
        std::string responseData;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, response_data_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

        // 执行请求
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {

            long response_code;
            // 获取HTTP状态码
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            cout<<"response code:"<<response_code<<endl;
            cout<<"response header:"<<responseHeader<<endl;
            // 响应数据存储在 responseData 中，可以进行解析或处理
            cout << "Response received:" << responseData<<std::endl;
            //handleCurlPostJsonParse(responseData);
            this->handleCurlPostJsonParse(responseData);
        }

        // 释放curl句柄和headers
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    } else {
        std::cerr << "初始化curl失败" << std::endl;
    }
}

void CurlTest::handleCurlPostJsonParse(const std::string& json) {
    Document document;
    document.Parse(json.c_str());

    // 检查解析是否成功
    if (document.HasParseError()) {
        std::cout << "解析JSON时出错" << std::endl;
    } else {
        // 从解析的JSON中提取数据
        if (document.HasMember("code") && document["code"].IsInt()) {
            int code = document["code"].GetInt();
            std::cout << "返回的code: " << code << std::endl;
        }

        if (document.HasMember("message") && document["message"].IsString()) {
            std::string message = document["message"].GetString();
            std::cout << "返回的message: " << message << std::endl;
        }

        if (document.HasMember("data") && document["data"].IsObject()) {
            const Value& data = document["data"];
            if (data.HasMember("userid") && data["userid"].IsString()) {
                std::string userId = data["userid"].GetString();
                std::cout << "返回的userid: " << userId << std::endl;
            }

            if (data.HasMember("token") && data["token"].IsString()) {
                std::string token = data["token"].GetString();
                std::cout << "返回的token: " << token << std::endl;
            }
        }
    }
}


