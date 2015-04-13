var lessonName = "lesson1";
var index = 1;
var input = "";
var mode = '2';
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
	var input = document.getElementsByClassName('radioMode');
	var i = findChecked(input);
	if(random)
	{
		random = false;
		document.getElementById('tagTitleMode').innerHTML = (input[i].id + " ⃠ Ran");
	}
	else
	{
		random = true;
		document.getElementById('tagTitleMode').innerHTML = (input[i].id + " Ran");
		index = Math.floor((Math.random() * (library[findIndex(lessonName)].length-1)) + 1);
		show();
	}
	document.getElementById('modeChoice').click();
}

function chooseLesson(input)
{
	var i = findChecked(input);
	lessonName = input[i].value;
	document.getElementById('tagTitleLesson').innerHTML = input[i].id;
	index = 0;
	execute();
	dict();
	document.getElementById('lessonChoice').click();
}

function chooseMode(input)
{
	var i = findChecked(input);
	mode = input[i].value;
	if(random) document.getElementById('tagTitleMode').innerHTML = (input[i].id + " Ran");
	else document.getElementById('tagTitleMode').innerHTML = (input[i].id + " ⃠ Ran");
	index = 0;
	execute();
	document.getElementById('modeChoice').click();
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
		logColor("● mode: ", "yellow", false); log(mode);
		logColor("● random: ", "yellow", false); log(random);
		logColor("● loading lesson: ", "yellow", false); log(lessonName);
		log(" ");
		window.setTimeout('show()',500);
		window.setTimeout('document.getElementById("result").innerHTML = "-";',3000);
		window.setTimeout('document.getElementById("inputBox").value = "";',0);
		return;
	}
	else
	{
		var result = document.getElementById("result");
		input = document.getElementById("inputBox").value;
		if(input[0] == '!')
		{
			result.innerHTML = "";
			if(commandInput(input))
				addText(result, "execute " + input, "green", true);
			else
				addText(result, "'" + input + "'" + " is an unknown command. Can not execute!", "red", true);
			window.setTimeout('document.getElementById("inputBox").value = "";',0);
			window.setTimeout('document.getElementById("result").innerHTML = "-";',3000);
			return;
		}
		switch(mode)
		{
			case '1':
				if(library[i][index].eng == input)
				{
					result.innerHTML = "";
					addText(result, "Correct!", "green", true);
				}
				else
				{
					result.innerHTML = "";
					addText(result, "Incorrect! Right answer is: ", "red", true);
					addText(result, library[i][index].eng, "gray", true);
				}
				break;
			case '2':
				if(library[i][index].romanji == input || library[i][index].jap == input)
				{
					result.innerHTML = "";
					addText(result, "Correct!", "green", true);
				}
				else
				{
					result.innerHTML = "";
					addText(result, "Incorrect! Right answer is: ", "red", true);
					addText(result, library[i][index].romanji, "gray", true);
					addText(result, library[i][index].jap, "gray", true);
				}
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
	logColor(document.getElementById("question").innerHTML, "lightblue", true);
	logColor("input: ", "yellow", false); log(input);
	logColor("output: ", "yellow", false); log(document.getElementById("result").innerHTML);
	window.setTimeout('show()',500);
	window.setTimeout('document.getElementById("result").innerHTML = "-";',3000);
	window.setTimeout('document.getElementById("inputBox").value = "";',0);
}

function dict()
{
	var dict = document.getElementById("dictionary");
	dict.innerHTML = " ";
	var i = findIndex(lessonName);
	var dictIndex = 1; //skip 'library[i]'s name'
	while(dictIndex < library[i].length)
	{
		addText(dict, "Romanji: ", "blue", false); addText(dict, library[i][dictIndex].romanji, "black", true);
		addText(dict, "Japanese: ", "blue", false); addText(dict, library[i][dictIndex].jap, "black", true);
		addText(dict, "English: ", "blue", false); addText(dict, library[i][dictIndex].eng, "black", true);
		var br = document.createElement("br"); dict.appendChild(br); //new line element
		dictIndex++;
	}
}

function toggleDict(checkBox)
{
	if(checkBox.checked)
	{
		document.getElementById(checkBox.name).style.top='400px';
	}
	else document.getElementById(checkBox.name).style.top='-64px';
}

function keyPress(e, submitButton)
{
	if (e == 13)
		submitButton.click();
}

function logColor(input, color, newline)
{
	var log = document.getElementById("log");
	var span = document.createElement("span");
	span.textContent = input;
	span.style.color = color;
	log.appendChild(span);
	if(newline)
	{
		var br = document.createElement("br");
    	log.appendChild(br);
	}
}

function log(input)
{
	var log = document.getElementById("log");
	log.innerHTML += input;
	var br = document.createElement("br");
    log.appendChild(br);
    /*auto scroll to bottom*/
	var chat_div = document.getElementById('logOverflow');
	chat_div.scrollTop = chat_div.scrollHeight;
}

function clearlog()
{
	document.getElementById("log").innerHTML = "Log:";
	log(" ");
}

function addText(target, input, color, newline)
{
	var span = document.createElement("span");
	span.textContent = input;
	span.style.color = color;
	target.appendChild(span);
	if(newline)
	{
		var br = document.createElement("br");
    	target.appendChild(br);
	}
}

function commandInputEmpty()
{
	var input = document.getElementById("logInput").value;
	commandInput(input);
}

function commandInput(command)
{
	var success = true;
	var tempCommand = command;
	switch(tempCommand[1]) /*check modifier*/
	{
		case 'F':
			if(document.getElementById('logTerminal').checked)
				document.getElementById('logTerminal').click();
			tempCommand = tempCommand[0] + tempCommand.substring(2, tempCommand.length); /*erase 'F'*/
			break;
	}
	switch(tempCommand)
	{
		case "!help":
			if(document.getElementById('logTerminal').checked != true)
				document.getElementById('logTerminal').click();
			logColor("execute " + tempCommand, "green", true);
			logColor("USEFUL tempCommandS:", "yellow", true);
			logColor("all commands start with !.", "lightblue", true);
			logColor("more commands will be added later.", "lightblue", true);
			logColor("● !clear --- clear the log terminal.");
			log("● !info  --- show/hide information about this page.");
			log("● !infoL  --- show information about this page in log.");
			log("● !lesson  --- show/hide lesson list.");
			log("● !mode  --- show/hide mode-selection page.");
			log("● !log  --- show/hide log terminal.");
			log("● !dict  --- show/hide dictionary.");
			log("● !goto p1 --- jump to entry 'p1' (p1 is int parameter).");
			logColor("USEFUL MODIFIER:", "yellow", true);
			logColor("all modifiers follow right after !.", "lightblue", true);
			logColor("more modifiers will be added later.", "lightblue", true);
			logColor("(modifier with empty command may work but throw error message.)", "lightblue", true);
			logColor("Ex: !Finfo --- force close log terminal before execute !info.", "lightblue", true);
			log("● F --- force close log terminal before execute.");
			log(" ");
			break;

		case "!clear":
			log("execute " + tempCommand);
			clearlog(); break;

		case "!infoL":
			logColor("execute " + tempCommand, "green", true);
			logColor("INFO:", "yellow", true);
			var pIndex = 0;
			while(pIndex < document.getElementsByTagName('p').length)
			{
				log(document.getElementsByTagName('p')[pIndex].innerHTML);
				pIndex++;
			}
			log(" ");
			break;

		case "!info":
			clearSlide(document.getElementById('introToggle'));
			logColor("execute " + tempCommand, "green", true);
			document.getElementById('introToggle').click(); break;

		case "!lesson":
			clearSlide(document.getElementById('lessonChoice'));
			logColor("execute " + tempCommand, "green", true);
			document.getElementById('lessonChoice').click(); break;

		case "!mode":
			clearSlide(document.getElementById('modeChoice'));
			logColor("execute " + tempCommand, "green", true);
			document.getElementById('modeChoice').click(); break;

		case "!log":
			logColor("execute " + tempCommand, "green", true);
			document.getElementById('logTerminal').click(); break;

		case "!dict":
			logColor("execute " + tempCommand, "green", true);
			document.getElementById('dictButton').click(); break;

		default: success = false; break;
	}
	switch(tempCommand.substring(0, tempCommand.indexOf(' '))) /* command with parameter*/
	{
		case "!goto":
			success = true;
			logColor("execute " + tempCommand, "green", true);
			tempCommand = tempCommand.substring(6, tempCommand.length);
			gotoEntry(tempCommand);
			break;
	}
	if(!success) logColor("'" + command + "'" + " is an unknown command. Can not execute!", "red", true);
	window.setTimeout('document.getElementById("logInput").value = "!";',0);

	/*auto scroll to bottom*/
	var chat_div = document.getElementById('logOverflow');
	chat_div.scrollTop = chat_div.scrollHeight;

	return success;
}

function toggle(checkBox)
{
	if(checkBox.checked)
	{
		document.getElementById(checkBox.name).style.left='0'; //show
	}
	else document.getElementById(checkBox.name).style.left='-580px'; //hidden
}

function clearSlide(exempt)
{
	var toggle = document.getElementsByClassName('toggle');
	var i = 0;
	while(i < toggle.length)
	{
		if(toggle[i] == exempt || toggle[i] == document.getElementById('dictButton') || toggle[i] == document.getElementById('logTerminal'))
		{
			i++;
			continue;
		}
		else
		{
			toggle[i].checked = false;
			document.getElementById(toggle[i].name).style.left='-580px'; 
			i++;
		}
	}
}

function slideCorrect(input)
{
	var dimension = input.getBoundingClientRect();
}

function gotoEntry(input)
{
	var integer = parseInt(input);
	var i = findIndex(lessonName);
	var max = library[i].length - 1;

	integer = integer%max;
	if(integer == 0) integer = max;

	index = integer;
	show();
}
