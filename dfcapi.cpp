#include <iostream>
using namespace std;

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include <stdio.h>
#include <curl/curl.h>

string URL = "10.220.18.61:6000/filecatalog_api/v1/";

namespace DFCAPI {

size_t writeFunction(void* ptr, size_t size, size_t nmemb, string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

string getFiles(string conditions,string username, string password){
  json creds;
  creds["username"] = username;
  creds["password"] = password;
  string str_creds = creds.dump();
  //const char *c_creds = str_creds.c_str(); to perfrom func. 
  return performRequest(conditions, str_creds, "GET");
}

string updateFileInfo(string pathToFile, json condition, string username, string password){
  condition["username"] = username;
  condition["password"] = password;
  string str_condition = condition.dump();
  return performRequest(pathToFile, str_condition, "PUT");
}
 
string deleteFileInfo(string pathToFile, string username, string password){
  json creds;
  creds["username"] = username;
  creds["password"] = password;
  string str_creds = creds.dump();
  return performRequest(pathToFile, str_creds, "DELETE");
}

string performRequest(string conditions, string json, string qType){
  CURL *curl;
  CURLcode res;
  string response_string;
 
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();
  if(curl) {
    cout << " curl initiated " << endl;
    conditions = URL + conditions;
    const char *curl_url = conditions.c_str(); 
    curl_easy_setopt(curl, CURLOPT_URL, curl_url);
 
    /* cache the CA cert bundle in memory for a week */
    curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);
    
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);    

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charset: utf-8");

    const char *c_json = json.c_str();  // what's the point of using nlohmann then? 
    const char *curl_customRequest = qType.c_str();   
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, curl_customRequest);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, c_json); // jsonObj
    cout << " before tha easy perform " << endl;
    /* Perform the request, res gets the return code */
    res = curl_easy_perform(curl);
    cout << " res = " << res << endl;
    /* Check for errors */
    if(res != CURLE_OK){
      cout << " res error and some pritnf where it is? " << endl;
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }
    cout << " the result is - " << response_string << endl;
    /* always cleanup */
    curl_easy_cleanup(curl);
  } 
  else {
    cout << " can't init curl " << endl;
  }
 
  curl_global_cleanup();

  return response_string;
}
int main(void)
{
  cout << " m? " ;
  return 0;
}

}