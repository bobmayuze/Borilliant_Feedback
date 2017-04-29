(function(){
  $.ajax({ 
    type : 'GET', 
    url : '/course_list.json', 
    async : false, 
  beforeSend : function(){/*loading*/},
  dataType : 'json', 
  success : function(result){
  var buffer = "";
  $.each(result, function(index, val){ 

    for(var i=0; i < val.length; i++){ 
      var item = val[i]; 
      console.log(item);
      buffer+=" <li><a href='#"+item.name+"'>"+item.name+"</a></li> <li><a href='#"+item.name+"'>"+item.name+"</a></li>"; 
    } 
    $('ul').html(buffer);
  });
 }
});
});