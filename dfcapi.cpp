#include <iostream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include <stdio.h>
#include <curl/curl.h>

namespace DFCAPI {

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

std::string getFiles(std::string condition,std::string name, std::string password){

}
 
std::string performRequest(){
  
}
int main(void)
{
  // here should be only func calls aka get
  // getFiles(string condition);
  // updateFileInfo(string pathToFile, string condition)
  // deleteFileInfo(string pathToFile)
  std::cout << " >>>main " << std::endl;
  CURL *curl;
  CURLcode res;
 
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();
  if(curl) {
    std::cout << " curl initiated " << std::endl;
    curl_easy_setopt(curl, CURLOPT_URL, "10.220.18.61:6000/filecatalog_api/v1/start_datetime=2023-02-01%2008%3A29%3A47|2023-02-02%2008%3A29%3A47");
 
    /* cache the CA cert bundle in memory for a week */
    curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);
    std::string response_string;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    json creds;
    creds["username"] = "shift";
    creds["password"] = "shift";
    std::string str_creds = creds.dump();
    const char *c_creds = str_creds.c_str();       // what's the point of using nlohmann then? 
    //char* jsonObj = "{ \"username\" : \"shift\" , \"password\" : \"shift\" }"; 
    

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charset: utf-8");

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, c_creds); // jsonObj
    std::cout << " before tha easy perform " << std::endl;
    /* Perform the request, res gets the return code */
    res = curl_easy_perform(curl);
    std::cout << " res = " << res << std::endl;
    /* Check for errors */
    if(res != CURLE_OK){
      std::cout << " res error and some pritnf where it is? " << std::endl;
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }
    std::cout << " the result is - " << response_string << std::endl;
    /* always cleanup */
    curl_easy_cleanup(curl);
  } 
  else {
    std::cout << " can't init curl " << std::endl;
  }
 
  curl_global_cleanup();
 
  return 0;
}

}