var lessonName = "lesson1";
var index = 1;
var input = "";
var mode = 1;

function chooseLesson(input)
{
	lessonName = input.value;
	index = 0;
	execute();
}

function chooseMode(input)
{
	mode = input.value;
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
	switch(mode)
	{
		case 1:
		{
			document.getElementById("question").innerHTML = index + "/" + (library[i].length-1) + ": " + library[i][index].romanji + " " + library[i][index].jap;
			break;
		}
		case 2:
		{
			document.getElementById("question").innerHTML = index + "/" + (library[i].length-1) + ": " + library[i][index].eng;
			break;
		}
	}
}

function execute()
{
	var i = findIndex(lessonName);
	if(index === 0)
	{
		document.getElementById("question").innerHTML = "Loading lesson: " + library[i][0];
		index++;
	}
	else
	{
		input = document.getElementById("inputBox").value;
		switch(mode)
		{
			case 1:
			{
				if(library[i][index].eng == input)
					document.getElementById("result").innerHTML = "right!";
				else
					document.getElementById("result").innerHTML = "wrong! Right answer is: " + library[i][index].eng;
				break;
			}
			case 2:
			{
				if(library[i][index].romanji == input || library[i][index].jap == input)
					document.getElementById("result").innerHTML = "right!";
				else
					document.getElementById("result").innerHTML = "wrong! Right answer is: " + library[i][index].romanji + " " + library[i][index].jap;
				break;
			}
		}
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
