#ifndef EVENTMARCO_H
#define EVENTMARCO_H

// 事件分发中
// 通过宏展开后所构造的类或者函数，会在这里面继续映射成其他别名

// Server用:

// 映射到登录request类中
#define MSG_LOGIN_REQ_Handler loginRequest
#define MSG_REGISTER_REQ_Handler registerRequest
#define MSG_FRIEND_LIST_REQ_Handler friendListRequest

// 服务端事件分发
#define SERVER_EVENT_DISPATCH_CASE(type, ...) { \
case type: \
type##_Handler handler(__VA_ARGS__); \
return; \
}


// Client用:
// emit
#define MSG_LOGIN_RESP_ALLOW_EMIT loginAllow
#define MSG_LOGIN_RESP_REJECT_EMIT loginReject
#define MSG_REGISTER_RESP_ALLOW_EMIT registerSuccess
#define MSG_REGISTER_RESP_REJECT_EMIT registerFail
#define MSG_FRIEND_LIST_RESP_EMIT friendListDisplayEmit


// 客户端事件分发 emit
#define Client_EVENT_DISPATCH_CASE(type, ...) { \
case type: \
emit type##_EMIT(__VA_ARGS__); \
return ; \
}

#endif // EVENTMARCO_H
