var config = {
     apiKey: "AIzaSyBnHshiXXjcuC-QBZlQKmf8o4aM0wNTZ6c",
    authDomain: "mayday-saddy.firebaseapp.com",
    databaseURL: "https://mayday-saddy.firebaseio.com",
    projectId: "mayday-saddy",
    storageBucket: "mayday-saddy.appspot.com",
    messagingSenderId: "499883644179"
  };
  firebase.initializeApp(config);
var ref = firebase.database().ref();
ref.on('value',gotData , errData);

function gotData(data)
{
	console.log(data.val());
	var values = data.val();
	var keys = Object.keys(values);
 	console.log(keys);
	
	for(var i=0 ; i<keys.length ; i++)
	{
		var k = keys[i];
		var ak = values[k].Button1;
		var sc = values[k].Button2;
		var sk = values[k].Button3;
		var dc = values[k].Button4;
		var sa = values[k].Smoke;
		var sb = values[k].Waterlevel;

		console.log(ak , sc, sk, dc, sa, sb);     
		if(ak === 1)
		{
			window.alert("POLICE");
			break;
		}
		
		if(sc === 1)
		{
			window.alert("Hospital");
			break;
		}
		
		if(sk === 1)
		{
			window.alert("Fire Station");
			break;
		}

		if(dc === 1)
		{
			window.alert("Family Members");
			break;
		}

		if(sa === 1)
		{
			window.alert("Fire Station");
			break;
		}

		if(sb === 1)
		{
			window.alert("Fire Station_flood");
			break;
		}

	}
}
function errData(err)
{
	console.log('Error!');
	console.log(err);
}




