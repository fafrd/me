var index = 0;
var input = "";

function show()
{
	document.getElementById("question").innerHTML = dictionary[index].eng;
}

function execute()
{
	input = document.getElementById("inputBox").value;
	if(dictionary[index].romanji != input)
		document.getElementById("result").innerHTML = "wrong!";
	else
		document.getElementById("result").innerHTML = "right!";
	index++;
	window.setTimeout('show()',500);
	window.setTimeout('document.getElementById("result").innerHTML = "";',500);
	window.setTimeout('document.getElementById("inputBox").value = ""',500);
}

function keyPress(e)
{
	if (e == 13)
		document.getElementById('submitButton').click();
}
