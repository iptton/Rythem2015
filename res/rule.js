function getMatchRule(host,path){
    var rule = null;
    if(host=="127.0.0.1"){
        rule = new Rule(TYPE_CONTENT,function(){
            var body = "hello from js <h1>You're requesting path:"+path+"</h1>";
            var contentLength = body.length;
           return "HTTP/1.1 200 OK\r\nConnection: Keep-Alive\r\nContent-Length: "+contentLength+"\r\n\r\n"+body;
        });
    }
    return rule.replacement();
}


var TYPE_CONTENT = 0;
var TYPE_BLOCK = 1;


function Rule(type,replacement){
    this.type = type;
    this.replacement = replacement;
}