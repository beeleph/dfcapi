#include "dfcapi.hpp"
using json = nlohmann::json;

int main(void){
    std::cout << "Test initiated " << std::endl; 
    std::string result;

    // GET
    result = DFCAPI::getFiles("start_datetime=2023-02-01%2008%3A29%3A47|2023-02-02%2008%3A29%3A47", "shift", "shift");
    std::cout << " result = " << result << std::endl;

    // PUT
    json condition;
    condition["run_number"] = "777";
    condition["target_particle"] = "CsI 146%";
    result = DFCAPI::updateFileInfo("bmn.nica.jinr/vo/test/someFile.data", condition, "shift", "shift");
    std::cout << " result = " << result << std::endl;   // nothing is basically OK

    // DELETE 
    result = DFCAPI::deleteFileInfo("bmn.nica.jinr/vo/test/someFile.data", "shift", "shift");
    std::cout << " result = " << result << std::endl;   // same
    return 0;
}