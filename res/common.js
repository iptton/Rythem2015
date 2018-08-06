
;function Rule(){};
(function(){
    Rule.prototype = {
        TYPE_LOCAL_CONTENT : 0,
        TYPE_BLOCK : 1,

        TYPE_DEFAULT_200:1200,
        TYPE_DEFAULT_404:1404,
        TYPE_DEFAULT_504:1504
    };




    function Rule(type,replacement){
        this.type = type;
        this.replacement = replacement;
    }

}());