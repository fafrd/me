var lessonName = "lesson1";
var index = 1;
var input = "";

function chooseLesson(input)
{
	lessonName = input.value;
	index = 0;
}

function findIndex(lessonName)
{
	var i = 0;
	while(i < library.length)
	{
		if(library[i][0] == lessonName) return i;
		i++;
	}
}

function show()
{
	var i = findIndex(lessonName);
	document.getElementById("question").innerHTML = library[i][index].eng;
}

function execute()
{
	var i = findIndex(lessonName);
	input = document.getElementById("inputBox").value;
	if(library[i][index].romanji != input)
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
