
var express =require('express');

var mongoose = require('mongoose');
var bodyParser = require('body-parser');
var methodOverride = require('method-override');



var app	=express();

//mongoose.connect('mongodb://localhost/cobil');
//mongoose.connect('mongodb+srv://-URLL DE BASE DE DATOS PARA PAGINA WEB- ');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:true}));


app.set('view engine','pug');
app.set('port',process.env.PORT||8080)
app.use(express.static("public"));
app.use(methodOverride('_method'));


app.get('/',function(sol,resp){
/*var data={
serial:'s2',
name:'.',
valor:'0',
actuador:'n',
}
var dates = new prog(data);
dates.save(function(err){
console.log(dates);
});*/
	resp.render('index')
})

app.get('/acerca',function(sol,resp){
	resp.render('acerca')
})

var programSchema=
{
	serial: String,
	name: String,
	valor: String,
	actuador: String,
};


var f = new Date();


var tdlSchema=
{	serial:String,
	valor: String,
};

var prog= mongoose.model('prog',programSchema);
	


//impresion de Datos
{

	app.get('/sensado/general',function(sol,resp)
		{		var id=sol.params.id;
			prog.findOne({'serial':'s1'||'s2'||'s3'||'s4'},function(error,dates)
			{console.log(dates);
				resp.render('sensado/general',{user:dates});
			}); 
		}); 
	app.get('/sensado/uno',function(sol,resp)
		{			
			prog.findOne({'serial':'s1'},function(error,dates)
			{console.log(dates);
				resp.render('sensado/uno',{user:dates});
			}); 
		}); 
	app.get('/sensado/dos',function(sol,resp)
		{
			prog.findOne({'serial':'s2'},function(error,dates)
			{console.log(dates);
				resp.render('sensado/dos',{user:dates});
			}); 
		}); 
	app.get('/sensado/tres',function(sol,resp)
		{
			
			prog.findOne({'serial':'s3'},function(error,dates)
			{console.log(dates);
				resp.render('sensado/tres',{user:dates});
			}); 
		}); 
	app.get('/sensado/cuatro',function(sol,resp)
		{			
			prog.findOne({'serial':'s4'},function(error,dates)
			{console.log(dates);
				resp.render('sensado/cuatro',{user:dates});
			}); 
		}); 
}

/////variable
{ var i=0;
	app.post("/catch/",function(sol,resp)
	{ 
		var cah={
			serial: sol.body.serial,
			name: sol.body.name,
			valor: sol.body.valor,
			actuador: sol.body.actuador,
			};
			console.log('Datos Recibidos');
			console.log(cah);
			
				prog.findOne({'serial': sol.body.serial},function(err,idlog)
				{ 

							
							var tempo={
							name:cah.name,
							valor:cah.valor,
							actuador:cah.actuador,
							};
			
						prog.update({'serial':sol.body.serial},tempo,function(rellando){});
						
								prog.find({'serial': sol.body.serial},function(erre,idloga){
									if(erre){console.log(erre);}
									else{console.log('datos Resguardados');}
								});																	
					
								console.log(err);
				});
	
		resp.render('catch/index',{data:cah});
	}); 


}
	app.get('/catch/index',function(sol,resp)
	{resp.render('catch/index',{data:'s'});}); 


///eliminar
var id;
{
app.get('/delete',function(sol,resp)
		{
			prog.findOne({'serial':'s2'},function(error,dates)
			{ id=dates._id;
			prog.remove({'_id':id},function(err)
				{if(err){console.log(err);}
				else{console.log('valor eliminado');}
				});
			});
			});		
}

//// acciones
var accion1='n';
var accion2='n';
var accion3='n';
var accion4='n';
{

	app.get( '/respuno', function ( req, res ) {
	prog.findOne({'serial':'s1'},function(error,dates){
			if(error){console.log(error);}
			else{//console.log('valores a contestar');
				//console.log(dates.actuador);
				accion1=dates.actuador							 
    		}});
    res.send( accion1 );
    } );
	app.get( '/respdos', function ( req, res ) {
	prog.findOne({'serial':'s2'},function(error,dates){
			if(error){console.log(error);}
			else{//console.log('valores a contestar');
				//console.log(dates.actuador);
				accion2=dates.actuador							 
    		}});
    res.send( accion2 );
    } );
	app.get( '/resptres', function ( req, res ) {
	prog.findOne({'serial':'s3'},function(error,dates){
			if(error){console.log(error);}
			else{//console.log('valores a contestar');
				//console.log(dates.actuador);
				accion3=dates.actuador							 
    		}});
    res.send( accion3 );
    } );
	app.get( '/respcuatro', function ( req, res ) {
	prog.findOne({'serial':'s4'},function(error,dates){
			if(error){console.log(error);}
			else{//console.log('valores a contestar');
				//console.log(dates.actuador);
				accion4=dates.actuador							 
    		}});
    res.send( accion4 );
    } );
}

///Renders
{



	app.get("/sensado/general",function(sol,resp)
	{resp.render('sensado/general',{fail:''});});

	app.get("/sensado/uno",function(sol,resp)
	{resp.render('sensado/uno',{fail:''});});

	app.get("/sensado/dos",function(sol,resp)
	{resp.render('sensado/dos',{fail:''});});

	app.get("/sensado/tres",function(sol,resp)
	{resp.render('sensado/tres',{fail:''});});

	app.get("/sensado/cuatro",function(sol,resp)
	{resp.render('sensado/cuatro',{fail:''});});

	app.get("/cuenta/index",function(sol,resp)
	{resp.render('cuenta/index');});  

	app.get("/cuenta/signin",function(sol,resp)
	{resp.render('cuenta/signin',{fail:''});});

	app.get("/admin/index",function(sol,resp)
	{resp.render('admin/index');});
	app.get("/admin/form",function(sol,resp)
	{resp.render('admin/form');});
	app.get('/cuenta/ingresar',function(sol,resp){
	resp.render('cuenta/ingresar')});

	app.get('/user/index',function(sol,resp)
	{	resp.render('user/index',{user:loginuser});});

}



app.listen(process.env.PORT || 8080,() => console.log('fine'))