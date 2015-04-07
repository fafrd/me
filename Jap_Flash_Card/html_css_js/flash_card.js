var lessonName = "lesson1";
var index = 1;
var input = "";
var mode = '1';
var random = false;

function findChecked(arrayInput)
{
	var i = 0;
	while(i < arrayInput.length)
	{
		if(arrayInput[i].checked) return i;
		i++;
	}
	return 0;
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

function chooseRandom()
{
	if(random) 	random = false;
	else
	{
		random = true;
		index = Math.floor((Math.random() * (library[findIndex(lessonName)].length-1)) + 1);
		show();
	}
}

function chooseLesson(input)
{
	var i = findChecked(input);
	lessonName = input[i].value;
	index = 0;
	execute();
}

function chooseMode(input)
{
	var i = findChecked(input);
	mode = input[i].value;
	index = 0;
	execute();
}

function show()
{
	var i = findIndex(lessonName);
	switch(mode)
	{
		case '1':
			document.getElementById("question").innerHTML = index + "/" + (library[i].length-1) + ": " + library[i][index].romanji + " --- " + library[i][index].jap;
			break;
		case '2':
			document.getElementById("question").innerHTML = index + "/" + (library[i].length-1) + ": " + library[i][index].eng;
			break;
		default: break;
	}
}

function execute()
{
	var i = findIndex(lessonName);
	if(index === 0)
	{
		input = "";
		document.getElementById("question").innerHTML = "● loading lesson: " + library[i][0];
		if(random)
		{
			index = Math.floor((Math.random() * (library[findIndex(lessonName)].length-1)) + 1);
		}
		else
		{
			index++;
		}
		log("● mode: " + mode + "	random: " + random + ".");
	}
	else
	{
		input = document.getElementById("inputBox").value;
		switch(mode)
		{
			case '1':
				if(library[i][index].eng == input)
					document.getElementById("result").innerHTML = "right!";
				else
					document.getElementById("result").innerHTML = "wrong! Right answer is: " + library[i][index].eng;
				break;
			case '2':
				if(library[i][index].romanji == input || library[i][index].jap == input)
					document.getElementById("result").innerHTML = "right!";
				else
					document.getElementById("result").innerHTML = "wrong! Right answer is: " + library[i][index].romanji + " --- " + library[i][index].jap;
				break;
			default: break;
		}
		if(random) index = Math.floor((Math.random() * (library[i].length-1)) + 1);
		else index++;
		if(index >= library[i].length) index = 1;
	}
	console.log(document.getElementById("question").innerHTML);
	console.log("input: 	" + input);
	console.log("output: " +document.getElementById("result").innerHTML);
	console.log(" ");
	log(document.getElementById("question").innerHTML);
	log("input: " + input);
	log("output: " +document.getElementById("result").innerHTML);
	log(" ");
	window.setTimeout('show()',500);
	window.setTimeout('document.getElementById("result").innerHTML = "-";',3000);
	window.setTimeout('document.getElementById("inputBox").value = "";',0);
}

function keyPress(e)
{
	if (e == 13)
		document.getElementById('submitButton').click();
}

function log(input)
{
	var log = document.getElementById("log");
	log.innerHTML += input;
	var br = document.createElement("br");
    log.appendChild(br);
    /*auto scroll to bottom*/
	var chat_div = document.getElementById('log');
	chat_div.scrollTop = chat_div.scrollHeight;
}

function clearlog()
{
	document.getElementById("log").innerHTML = "Log:;
}

