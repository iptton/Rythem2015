function getMatchRule(host,path){
    var rule = null;

    if(host.indexOf("qq.com") != -1){
        rule = {
            "replacement":"/Users/ippan/CLionProjects/QtInClion/cmake-build-debug/Rythem2015.app/Contents/Resources"+path,
            "type":0
        }
    }else{
        rule = {
            "type":-1
        }
    }
    return rule;
}




