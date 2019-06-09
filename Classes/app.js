server = require('http').Server();
var socketIO = require('socket.io');
var io = socketIO.listen(server);

//module doc, ghi, compile va run file cpp (c/c++)
var spawn = require('child_process').spawn;
var fs = require('fs')

//module connect database
var mysql = require('mysql');
var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "",
  database: "cocos_game"
});

//kiểm tra connect database
con.connect();

io.sockets.on('connection', function(socket){
	console.log('Client '+socket.id +' connecting...');
	socket.on('Hello', function(data){
		var mes = JSON.parse(data)
		console.log("Client "+ socket.id +" Say: Your Name is " + mes.Name + " and was born: " + mes.NgaySinh+" and Come From: " + mes.QueQuan);
		io.sockets.emit('Hello', {Name: mes.Name, NgaySinh : mes.NgaySinh, QueQuan : mes.QueQuan});
		
	});


	//kiểm tra đăng nhập
	socket.on('_Log_in_', function(data){
		var mes = JSON.parse(data)
		console.log(data);
		console.log(mes.username +"_"+mes.password);
		con.query("SELECT *FROM `player` WHERE player.username like '" + mes.username + "' and player.password like '"+ mes.password +"'",
			function (error, result, fields) {
				if (error) throw error;
				if(result.length == 1){
				socket.emit('_Check_Login_', {Check: result[0].id});	
				}
				else{
					socket.emit('_Check_Login_', {Check: 0});
				}
		});
	});

	//lay thong tin nguoi choi
	socket.on('Get_infor_Player', function(data){
		var mes = JSON.parse(data)
		//console.log(mes.username +"_"+mes.password);
		con.query("SELECT * FROM `player` WHERE player.id = "+ mes.id, 
			function (error, result, fields) {
				if (error) throw error;
				socket.emit('Get_infor_Player', {id: mes.id, username: result[0].username, password: result[0].password, experience: result[0].experience, correct_answer: result[0].correct_answer, wrong_answer: result[0].wrong_answer, total_win: result[0].total_win, total_lose: result[0].total_lose, total_kill: result[0].total_kill, friendship_point: result[0].friendship_point, friendship_level: result[0].friendship_level, room_name: result[0].room_name, submit_available: result[0].submit_available, status: result[0].status});
		});
	});


	//tạo phòng
	socket.on('Create_Room', function(data){
		var mes = JSON.parse(data)
		//console.log(mes.username +"_"+mes.password);
		con.query("UPDATE `player` set player.room_name = '1' where player.id = " + mes.id, 
			function (error, result, fields) {
				if (error) throw error;
				console.log('create room success');
		});
	});

	//hủy Phòng
	socket.on('Destroy_Room', function(data){
		var mes = JSON.parse(data)
		//console.log(mes.username +"_"+mes.password);
		con.query("UPDATE `player` set player.room_name = '0' where player.id = " + mes.id, 
			function (error, result, fields) {
				if (error) throw error;
				//io.sockets.emit('Destroy_Room', {Room: mes.Room, id: mes.id});
				console.log('destroy room success');
		});
	});


	socket.on('Update_Room', function(data){
		var mes = JSON.parse(data)
		//console.log(mes.username +"_"+mes.password);
		con.query("UPDATE `player` set player.room_name = '1' where player.id = " + mes.OppenontId, 
			function (error, result, fields) {
				if (error) throw error;
				io.sockets.emit('Update_Room', {Room: mes.Room, CurrentId: mes.OppenontId});
				console.log('update room success');
		});
	});

	socket.on('Join_Room', function(data){
		var mes = JSON.parse(data)
		var room_name = mes.OppenontId+'_'+mes.CurrentId;
		console.log(mes.OppenontId +"_"+mes.CurrentId);
		con.query("UPDATE `player` set player.room_name = '0' where player.id = " + mes.OppenontId + " or player.id = "+ mes.CurrentId, 
			function (error, result, fields) {
				if (error) throw error;
				io.sockets.emit('Join_Room', {Room: room_name});
				console.log('join success');
		});
	});

	//lấy danh sách phòng chờ
	socket.on('_Get_List_Room_', function(data){
		var mes = JSON.parse(data)
		//console.log(mes.username +"_"+mes.password);
		con.query("SELECT * FROM `player` WHERE player.room_name like '1'", 
			function (error, result, fields) {
				if (error) throw error;
				if(result.length >= 1){
				var _Get_List_Room_  = {CountRoom: result.length};
		    	for(var i = 0; i < result.length; i++)
		    	{
		    		var key = "Room"+i;
		    		var value = result[i].id;
		    		_Get_List_Room_[key] = value;
		    		var key = "username"+i;
		    		var value = result[i].username;
		    		_Get_List_Room_[key] = value;

		    	}
		    	
				socket.emit('_Get_List_Room_', {_Get_List_Room_});	
				console.log(_Get_List_Room_);
				}
				else{
					socket.emit('_Get_List_Room_', {_Get_List_Room_: {CountRoom: 0}});
				}
		});
	});


	//lấy danh sách rank
	socket.on('_Get_List_Rank_', function(data){
		var mes = JSON.parse(data)
		//console.log(mes.username +"_"+mes.password);
		con.query("SELECT * FROM `player` GROUP BY player.total_score DESC", 
			function (error, result, fields) {
				if (error) throw error;

				var _Get_List_Rank_  = {CountRank: result.length};
		    	for(var i = 0; i < result.length; i++)
		    	{
		    		var key = "id"+i;
		    		var value = result[i].id;
		    		_Get_List_Rank_[key] = value;
		    		var key = "username"+i;
		    		var value = result[i].username;
		    		_Get_List_Rank_[key] = value;
		    		var key = "total_score"+i;
		    		var value = result[i].total_score;
		    		_Get_List_Rank_[key] = value;
		    		var key = "total_question"+i;
		    		var value = result[i].total_question;
		    		_Get_List_Rank_[key] = value;
		    	}
		    	
				socket.emit('_Get_List_Rank_', {_Get_List_Rank_});	
				//console.log(_Get_List_Rank_);
		});
	});

	//bắt cặp người chơi ngẩu nhiên
	socket.on('_Find_The_Opponent_', function(data){
		var mes = JSON.parse(data)
		//console.log(mes.username +"_"+mes.password);
		con.query("SELECT * FROM `player` WHERE player.ready like '1' and player.id != "+ mes.id,
			function (error, result, fields) {
				if (error) throw error;
				if(result.length == 1){
					//io.sockets.emit('_Find_The_Opponent_', {Room: result[0].id +"_"+mes.id});
					con.query("SELECT * FROM `player` WHERE player.id != "+ result[0].id,
					function (error, results, fields) {
					if (error) throw error;
						io.sockets.emit('_Find_The_Opponent_', {Room: result[0].id +"_"+mes.id ,id: results[0].id, username: results[0].username});
						console.log(results[0].username);
						con.query("UPDATE `player` set player.ready = '0' where player.id = " + result[0].id,
						function (error, result, fields) {
							if (error) throw error;
							console.log('ok')
					});
					});

				}
				else{
					con.query("UPDATE `player` set player.ready = '1' where player.id = " + mes.id,
						function (error, result, fields) {
							if (error) throw error;
							socket.emit('_Find_The_Opponent_', {Room: "Doi Nguoi Choi Khac"});
					});
				}
		});
	});


	//chủ phòng nhấn nút play
	socket.on('_Ready_', function(data){
		var mes = JSON.parse(data)
		io.sockets.emit('_Ready_', {Room: mes.Room});
	});


	//chủ phòng đuổi người chơi ra khỏi phòng
	socket.on('_Chase_Player_', function(data){
		var mes = JSON.parse(data)
		io.sockets.emit('_Chase_Player_', {Room: mes.Room, CurrentId: mes.OppenontId});
	});


	//compile code c/c++ onl
	socket.on('_Get_Code_C_', function(code){
		var mes = JSON.parse(code);
		//console.log(mes.code);
		con.query("SELECT * FROM `test_case` WHERE test_case.question = " + mes.id_question, 
		function (error, result, fields) {
    	if (error) throw error;
		var code = {	include: '#include <stdio.h>', 
						marth: '#include <stdlib.h>',
						function: mes.code,
						//function: 'int soNguyenTo(int n){ \n if (n <= 1) \n return 0;\n for (int i = 2; i < n; i++) \n if (n % i == 0)\n return 0;\n return 1; \n } \n int PlayerFunction(int soA, int soB){ \n if(soNguyenTo(soA) == 1 && soNguyenTo(soB) == 1) \n return 1; \n return 0;}',
						void: 'int main(){ int dem = 0;',
						testCase_1: "if("+result[0].content + "==" + result[0].result+"){dem++;}",
						testCase_2: "if("+result[1].content + "==" + result[1].result+"){dem++;}",
						testCase_3: "if("+result[2].content + "==" + result[2].result+"){dem++;}",
						testCase_4: "if("+result[3].content + "==" + result[3].result+"){dem++;}",
						footer:'printf("%d ", dem); return 0;}'
					};
		fs.writeFile('HelloWord.cpp', code.include + '\n'+code.marth +'\n' + code.function +'\n' + code.void +'\n' + code.testCase_1+'\n' + code.testCase_2+'\n' + code.testCase_3+'\n' + code.testCase_4+'\n' +code.footer, 'utf8', function(err){
			if(err)
				throw err
			else
			{
				console.log('ghi file thanh cong!');
				var detail = '';
				var error = 0;
				var compile = spawn('gcc', ['HelloWord.cpp']);
				compile.stdout.on('data', function (data) {
				    console.log('stdout: ' + data);
				});
				//log error code;
				compile.stderr.on('data', function (data) {
				    console.log(String(data));
				    //socket.emit('_Get_Code_C_', {error: 1, detail: data});
				    detail = String(data);
				});

				if(data === 1)
				{
					compile.stderr.pipe(process.stderr);
				}

				compile.on('close', function (data) {
				    if (data === 0) {
				        var run = spawn('./a.exe', []);
				        //log ra result khi code true
				        run.stdout.on('data', function (output) {
				           console.log(String(output));
				           //socket.emit('_Get_Code_C_', {error: 0, detail: output});
				           detail = String(output);
				        });
				        run.stderr.on('data', function (output) {
				            console.log(String(output));
				        });
				        run.on('close', function (output) {
				            console.log('stdout: ' + output);
				        });
				    }
				})
				socket.emit('_Get_Code_C_', {error: error, detail: detail});
			}
		});

		//socket.emit('Create_Unit', {Room: mes.Room, name: mes.name, line: mes.line, id: mes.id});
	});
	});



	//chọn hệ
	socket.on('_Select_Element_', function(data){
		var mes = JSON.parse(data)
		io.sockets.emit('_Select_Element_', {elementName: mes.elementName, Room: mes.Room, Id: mes.Id});
	});
	
	//cấm
	socket.on('_Prohibit_Card_', function(data){
		var mes = JSON.parse(data)
		console.log(mes.OppenontId);
		io.sockets.emit('_Prohibit_Card_', {cardName: mes.cardName, Room: mes.Room, CurrentId: mes.OpponentId});
	});
	
	//chọn
	socket.on('_Pick_Card_', function(data){
		var mes = JSON.parse(data)
		io.sockets.emit('_Pick_Card_', {cardName: mes.cardName, Room: mes.Room, Id: mes.Id});
	});

	//upgrade kingdom
	socket.on('_Upgrade_Kingdom_', function(data){
		var mes = JSON.parse(data)
		io.sockets.emit('_Upgrade_Kingdom_', {Room: mes.Room, Id: mes.Id});
	});

	//tạo lính
	socket.on('Create_Unit', function(data){
		var mes = JSON.parse(data)
		//console.log("Level: " + mes.Level);
		io.sockets.emit('Create_Unit', {Room: mes.Room, name: mes.name, line: mes.line, id: mes.id});
	});

	//userSkill
	socket.on('Use_Skill', function(data){
		var mes = JSON.parse(data)
		//console.log("Level: " + mes.Level);
		io.sockets.emit('Use_Skill', {Room: mes.Room, name: mes.name, unitId: mes.unitId, id: mes.id});
	});

	//send message
	socket.on('Send_Message', function(data){
		var mes = JSON.parse(data)
		//console.log("Level: " + mes.Level);
		io.sockets.emit('Send_Message', {Room: mes.Room, content: mes.content});
	});


	//lấy câu hỏi theo level
	socket.on('_Level_', function(data){
		var mes = JSON.parse(data)
		console.log("Level: " + mes.Level);
	//truy vấn
	con.query("SELECT * FROM `question` WHERE question.level = "+ mes.Level +" and question.type = 1 ORDER BY RAND() LIMIT 1", 
	function (error, results, fields) {
    if (error) throw error;
	con.query("SELECT * FROM `test_case` WHERE test_case.question = " + results[0].id, 
	function (error, result, fields) {
    if (error) throw error;
	//get result to client
	io.sockets.emit('_Question_is_', {Room: mes.Room,
									id: results[0].id, 
									content: results[0].content, 
									level: results[0].level, 
									answer: results[0].answer,
									answer1: result[0].content,
									answer2: result[1].content,
									answer3: result[2].content,
									answer4: result[3].content});
		});
	});
	});
	
	socket.on('disconnect', function(data){
		console.log('Client '+socket.id +' disconnect');
	});
});

server.listen(process.env.PORT||3000);
console.log('Server 3000 listenning');


 

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		