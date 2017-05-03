window.onload = function() {

  $.ajaxSetup({beforeSend: function(xhr) {
    if (xhr.overrideMimeType)
    {
      xhr.overrideMimeType("application/json");
    }
  }
  });

  $.getJSON("course_list_origin.json", function(ret){
    json = ret["courses"];
    DP = getParameterByName('DP');
    console.log(DP);
    update(DP);
  });
};

function predicateBy(prop) {
  return function(a,b){
    if( a[prop] > b[prop]){
      return 1;
    }else if( a[prop] < b[prop] ){
      return -1;
    }
    return 0;
  }
};

// var json;
// var DP = -1;

function getParameterByName(name, url) {
  if (!url) url = window.location.href;
  name = name.replace(/[\[\]]/g, "\\$&");
  var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
  results = regex.exec(url);
  if (!results) return null;
  if (!results[2]) return '';
  return decodeURIComponent(results[2].replace(/\+/g, " "));
}

function update(id) {
  let list = $('#classList');
  list.empty();
  let filtered = [];
  // console.log(id);
  // console.log(json);
  for (let i=0; i<json.length; i++){
    if (json[i]["department_id"] === Number(id)){
      filtered.push(json[i]);
    }
  }
  filtered.sort(predicateBy("number"));
  let name = getMajor(id);
  console.log(name);
  console.log(id);
  for (let c=0; c<filtered.length; c++){
    list.append('\
      <li>\
        <div class="collapsible-header active">\
        <i class="material-icons">done</i>\
        <font size="5"color=#5390BE>'+name+' '+filtered[c]["number"]+" - "+filtered[c]["name"]+'</font>\
        </div>\
        \
        <div class="collapsible-body"><span>\
          <div style="margin: 0% 10% 0% 10%">\
          \
            <table style="table-layout: fixed; width:100%;">\
              <thead>\
                <tr>\
                  <td style="word-wrap: break-word">Feedback1</td>\
                </tr>\
                <tr>\
                  <td style="word-wrap: break-word">Feedback2</td>\
                </tr>\
                <tr>\
                  <td style="word-wrap: break-word">Feedback3</td>\
                </tr>\
              </thead>\
            \
              <tbody>\
                <tr><td>\
                  <a href="newFB.html?Course='+filtered[c]["id"]+'">\
                  <button class="light-blue btn waves-effect waves-light right" type="submit" name="action" style="margin-top: 5px; margin-left:10px;">Add a Feedback</button>\
                  </a>\
                  <!-- Modal Trigger -->\
                  <a class="light-blue btn waves-effect waves-light right modal-trigger" style="margin-top: 5px;" href="#'+'DS'+filtered[c]["id"]+'">Course Description</a>\
                  <!-- Modal Structure -->\
                  <div id="'+'DS'+filtered[c]["id"]+'" class="modal bottom-sheet">\
                  \
                    <div class="modal-content">\
                      <h4>'+name+' '+filtered[c]["number"]+" - "+filtered[c]["name"]+'</h4>\
                      <p>'+filtered[c]["description"]+'</p>\
                      <p>Credit Hours: '+filtered["max_credits"]+'</p>\
                    </div>\
                  \
                  </div>\
                \
                </td></tr>\
              </tbody>\
            </table>\
          \
          </div>\
        \
        </span></div>\
      </li>');
  }
};