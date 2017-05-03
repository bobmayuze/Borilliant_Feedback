var course_id;
var professor;
var overall;
var prof_rate;
var lec_diff;
var quality;
var hw_load;
var hw_diff;
var ex_diff;
var grade;
var attendence;
var iclicker;
var textbook;
var comment;

window.onload = function() {
	course_id = getParameterByName('Course');
	console.log(course_id);
}

function getParameterByName(name, url) {
  if (!url) url = window.location.href;
  name = name.replace(/[\[\]]/g, "\\$&");
  var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
  results = regex.exec(url);
  if (!results) return null;
  if (!results[2]) return '';
  return decodeURIComponent(results[2].replace(/\+/g, " "));
}

function getContent() {
	let select = document.getElementById("");
	professor = select.options[select.selectedIndex].text;
	// professor = select.options[select.selectedIndex].value;
	console.log(professor);

	overall = document.getElementById("overall").value;
	console.log(overall);

	prof_rate = document.getElementById("prof_rate").value;
	console.log(prof_rate);

	lec_diff = document.getElementById("lec_diff").value;
	console.log(lec_diff);

	hw_load = document.getElementById("hw_load").value;
	console.log(hw_load);

	hw_diff = document.getElementById("hw_diff").value;
	console.log(hw_diff);

	ex_diff = document.getElementById("ex_diff").value;
	console.log(ex_diff);

	grade = document.querySelector('input[name="grade"]:checked').id.substr(-1);
	console.log(grade);

	attendence = document.querySelector('input[name="attendence"]:checked').id.substr(-1);
	console.log(attendence);

	iclicker = document.querySelector('input[name="iclicker"]:checked').id.substr(-1);
	console.log(iclicker);

	textbook = document.querySelector('input[name="textbook"]:checked').id.substr(-1);
	console.log(textbook);

	comment = document.getElementById("comment").value;
	console.log(comment);
}

function sendToDB(
	course_id,
	professor, 
	overall, 
	prof_rate, 
	lec_diff, 
	quality, 
	hw_load, 
	hw_diff, 
	ex_diff,
	grade,
	attendence,
	iclicker,
	textbook,
	comment) {

	getContent();



}

function resetAll() {
	document.getElementById("professor").selectedIndex = 0;
}
