FLAGS=-Wall -O3
LIBS=-L/usr/local/lib -lpthread -lzmq -lprotobuf-c

all:	client server

test:	client_test server

client:
	gcc $(FLAGS) \
	    Client/main.c \
	    Client/client.c \
	    Client/Messages/insert_request.c \
	    Client/Messages/insert_response.c \
	    Client/Messages/delete_request.c \
	    Client/Messages/delete_response.c \
	    Client/Messages/query_by_id_request.c \
	    Client/Messages/query_by_id_response.c \
	    Client/Messages/query_by_compensation_range_request.c \
	    Client/Messages/query_by_compensation_range_response.c \
	    Common/tools.c \
	    Common/Data/common.pb-c.c \
	    Common/Data/insert_req.pb-c.c \
	    Common/Data/insert_res.pb-c.c \
	    Common/Data/delete_req.pb-c.c \
	    Common/Data/delete_res.pb-c.c \
	    Common/Data/query_by_id_req.pb-c.c \
	    Common/Data/query_by_id_res.pb-c.c \
	    Common/Data/query_by_compensation_range_req.pb-c.c \
	    Common/Data/query_by_compensation_range_res.pb-c.c \
	    $(LIBS) -o client

client_test:
	gcc $(FLAGS) -DTEST \
	    Client/main.c \
	    Client/client.c \
	    Client/Messages/insert_request.c \
	    Client/Messages/insert_response.c \
	    Client/Messages/delete_request.c \
	    Client/Messages/delete_response.c \
	    Client/Messages/query_by_id_request.c \
	    Client/Messages/query_by_id_response.c \
	    Client/Messages/query_by_compensation_range_request.c \
	    Client/Messages/query_by_compensation_range_response.c \
	    Client/Testcases/testcases.c \
	    Client/Testcases/test_insert.c \
	    Client/Testcases/test_delete.c \
	    Client/Testcases/test_query_by_id.c \
	    Client/Testcases/test_query_by_compensation.c \
	    Common/tools.c \
	    Common/Data/common.pb-c.c \
	    Common/Data/insert_req.pb-c.c \
	    Common/Data/insert_res.pb-c.c \
	    Common/Data/delete_req.pb-c.c \
	    Common/Data/delete_res.pb-c.c \
	    Common/Data/query_by_id_req.pb-c.c \
	    Common/Data/query_by_id_res.pb-c.c \
	    Common/Data/query_by_compensation_range_req.pb-c.c \
	    Common/Data/query_by_compensation_range_res.pb-c.c \
	    $(LIBS) -o client

server:
	gcc $(FLAGS) \
	    Server/main.c \
	    Server/server.c \
	    Server/Database/database.c \
	    Server/Database/rbtree.c \
	    Server/Messages/insert_request.c \
	    Server/Messages/insert_response.c \
	    Server/Messages/delete_request.c \
	    Server/Messages/delete_response.c \
	    Server/Messages/query_by_id_request.c \
	    Server/Messages/query_by_id_response.c \
	    Server/Messages/query_by_compensation_range_request.c \
	    Server/Messages/query_by_compensation_range_response.c \
	    Common/tools.c \
	    Common/Data/common.pb-c.c \
	    Common/Data/insert_req.pb-c.c \
	    Common/Data/insert_res.pb-c.c \
	    Common/Data/delete_req.pb-c.c \
	    Common/Data/delete_res.pb-c.c \
	    Common/Data/query_by_id_req.pb-c.c \
	    Common/Data/query_by_id_res.pb-c.c \
	    Common/Data/query_by_compensation_range_req.pb-c.c \
	    Common/Data/query_by_compensation_range_res.pb-c.c \
	    $(LIBS) -o server

clean:
	rm -rf client server
