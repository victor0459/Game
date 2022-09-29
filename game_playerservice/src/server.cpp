#include "lars_reactor.h"
#include<string.h>
#include"config_file.h"
#include"player_manager.h"
tcp_server *server;
playerManager pm;
//当前任务的一个task callback
void print_lars_task(event_loop *loop,void *args)
{
	printf("======active task func=======\n");
	//得到当前thread在线的fd有哪些
	listen_fd_set fds;
	loop->get_listen_fds(fds);

	listen_fd_set::iterator it;
	//遍历
	for(it=fds.begin();it!=fds.end();it++){
		int fd=*it;//当前线程已经建立链接并且监听中当前在线客户端
		tcp_conn *conn=tcp_server::conns[fd];//取出链接
		if(conn!=NULL){
			int msgid=404;
			const char *msg="Hello I am a Task!";
			conn->send_message(msg,strlen(msg),msgid);
		}

	}
}

void player_move(const char *data,uint32_t len,int msgid,net_connection *conn,void *user_data){
	//printf("-------------------move- data=%s\n",data);
	msg_body mb;
	memcpy(&mb,data,28);
	//printf("move speed=%f, px=%f\n",mb.speed,mb.p_x);
	tcp_conn*tc=dynamic_cast<tcp_conn*>(conn);
	if(tc==NULL){
		return ;
	}
	int connfd=tc->get_fd();
	//player p;
	//pm.find_player(connfd,p);
	//plays_online_map_it it=tcp_server::plays_map.begin();
	for(plays_online_map_it it=tcp_server::plays_map.begin();it!=tcp_server::plays_map.end();it++){
		//int fd=*it;//当前线程已经建立链接并且监听中当前在线客户端
		tcp_conn *conn=it->second;//取出链接
		if(connfd==it->first){
			continue;
		}
		if(conn!=NULL){

			int msgid=1004;
			const char*msg="move";
			conn->send_message(msg,strlen(msg),msgid);
		}

	}
	//printf("------------------move end-------------------------\n");

}
void player_up(const char *data,uint32_t len,int msgid,net_connection *conn,void *user_data){
	printf("新客户连接成功 %ld\n",strlen(data));
	msg_body mb;
	memcpy(&mb,data,28);
	printf("move speed=%f, px=%f\n",mb.speed,mb.p_x);


	tcp_conn*tc=dynamic_cast<tcp_conn*>(conn);
	int connfd=tc->get_fd();
	for(plays_online_map_it it=tcp_server::plays_map.begin();it!=tcp_server::plays_map.end();it++){
		tcp_conn *conn=it->second;
		if(connfd==it->first){
			continue;
		}
		if(conn!=NULL){
			int msgid=1001;
			//const char*msg="move";
			conn->send_message(data,strlen(data),msgid);
		}
	}

}
void print_busi(const char *data,uint32_t len,int msgid,net_connection *conn,void *user_data){
	printf("-------------来自客户端的数据%s\n",data);

}

//新的客户端创建成功之后的回调
void on_client_build(net_connection *conn,void *args){
	printf("新客户端连接---->\n");
	player* play=new player();
	//TODO 数据库获取修改
	tcp_conn*tc=dynamic_cast<tcp_conn*>(conn);
	if(tc==NULL){
		return;
	}
	int connfd=tc->get_fd();
	pm.player_add(connfd,play);
	int msgid=1500;
	int msgids=1501;
	//向新登录的客户端发送已经在线的客户端数据
	//const char*msg="hello";
	//conn->send_message(msg,strlen(msg),msgid);

	//向已经在线客户端发送新登录客户端数据
	for(plays_online_map_it it=tcp_server::plays_map.begin();it!=tcp_server::plays_map.end();it++){
		tcp_conn *conn=it->second;
		if(connfd==it->first){
			const char*msg="hello";
			conn->send_message(msg,strlen(msg),msgid);
			continue;
		}
		if(conn!=NULL){
			player p;
			p.speed=3.0f;
			p.px=2.25f;
			p.py=29.0f;
			p.pz=-13.0f;
			p.rx=0.0f;
			p.ry=0.0f;
			p.rz=0.0f;
			char* data=new char[28];
			memcpy(data,&p,28);
			conn->send_message(data,28,msgids);
		}
	}
	//每次客户端在创建链接成功之后
	//server->get_thread_pool()->send_task(print_lars_task);

	//给当前的conn绑定一个自定义参数，供之后来使用
	//const char *conn_param_test="I am the conn param for you!";
	//conn->param=(void*)conn_param_test;
}

//客户端断开之前的回调
void on_client_lost(net_connection *conn,void *args){
	tcp_conn*tc=dynamic_cast<tcp_conn*>(conn);
	if(tc==NULL){
		return;
	}
	int connfd=tc->get_fd();
	pm.player_del(connfd);
	printf("connection is lost\n");
}
int main()
{ 
	event_loop loop;
	//playerManager pM;
	//加载配置文件
	config_file::setPath("../conf/reactor.ini");
	std::string ip = config_file::instance()->GetString("reactor","ip","0.0.0.0");
	short port = config_file::instance()->GetNumber("reactor","port",8888);

	server= new tcp_server(&loop, ip.c_str(),port);
	
	
	//注册一些回调方法
	//server->add_msg_router(1,callback_busi);
	server->add_msg_router(1,print_busi);
	server->add_msg_router(1000,player_up);
	server->add_msg_router(2000,player_move);
	//注册连接hook函数
	server->set_conn_start(on_client_build);
	server->set_conn_close(on_client_lost);
	


	loop.event_process();

	return 0;
}
