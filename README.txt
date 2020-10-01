We have provided some wrapper functions so that it's easier for you to create RPC clients and servers. You can find the function declarations in a1_lib.h. To summarize, here is how you can use them:

- To create a server, you need the functions create_server() and accept_connection()
- For a client program to connect to a server, you can use connect_to_server()
- To send a message from a client to a server (or vice versa), use the function send_message()
- To receive a message, use the function recv_message().

For a concrete implementation of a simple client/server, you can refer to the example_*.c files. To run the example, do the following:
    - In a terminal, run 'make example'.
    - Start the server by running './a1_example_server'.
    - Start the client in another terminal by running './a1_example_client'.
    - Type something in the client terminal and hit enter. You will see the message show up on the server's stdout.
    - To stop the program, enter the message 'quit' in the client terminal.
    - Run 'make clean' to remove the executables.

