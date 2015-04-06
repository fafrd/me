var lessonName = "lesson1";
var index = 1;
var input = "";

function chooseLesson(input)
{
	lessonName = input.value;
	index = 0;
	execute();
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
	document.getElementById("question").innerHTML = index + "/" + (library[i].length-1) + ": " + library[i][index].eng;
}

function execute()
{
	var i = findIndex(lessonName);
	if(index == 0)
	{
		document.getElementById("question").innerHTML = "Loading lesson: " + library[i][0];
		index++;
	}
	else
	{
		input = document.getElementById("inputBox").value;
		if(library[i][index].romanji == input || library[i][index].jap == input)
			document.getElementById("result").innerHTML = "right!";
		else
			document.getElementById("result").innerHTML = "wrong! Right answer is: " + library[i][index].romanji;
		index++;
		if(index >= library[i].length) index = 1;
	}
	window.setTimeout('show()',500);
	window.setTimeout('document.getElementById("result").innerHTML = "";',3000);
	window.setTimeout('document.getElementById("inputBox").value = ""',500);
}

function keyPress(e)
{
	if (e == 13)
		document.getElementById('submitButton').click();
}
