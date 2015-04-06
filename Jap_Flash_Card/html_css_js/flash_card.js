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
}
