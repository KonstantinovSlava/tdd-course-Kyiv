#include <gtest/gtest.h>

#include "connecionwrapper.h"
#include "utils.h"

using namespace testing;
/*
Implement chat application, that communicates via TCP sockets.
 There is list of requirenments to this application:
 * It receives user nickname through commandline arguments on start
 * It runs only for two clients
 * On start it checks if port 4444 is bound
    * if it is - connects to other client
    * if not - binds a port and waits for inbound connection
        * message "No one is here..." is displayed in UI
 * After establishing connection - handshake is performed:
    * client writes message with it's nickname and ':HELLO!' string to socket ("client:HELLO!")
    * server responses with it's nickname and ':HELLO!' magic ("server:HELLO!")
        * if server receives malformated message - it drops connection with this client
        * if client receives malformated message - it drops connection and exits
            * Error message is shown
    * Listening socket must be closed
        (i) More than one client is not allowed to connect

 * It must send messages via created connection, until it is dropped
    * Application outputs "me: " prefix for user input
    * User inputs message through console interface and presses ENTER
    * Text message is sent to socket
 * It must receive messages via created connection, until it is dropped
    * Message received through socket
    * Line with message and '@friend_name: ' prefix is displayed ("metizik: Hello!")
 * END of message is determined by '\0' byte
 * When connection is dropped by one of users
    * "You are alone now" message is displayed to user
    * Application exits

  (i) Client starts dialog

 OPTIONAL requirement:
    * If user enters '!exit!' message, application must close connection and exit
    * If user runs app with 'me' nickname - error with text "Username me is reserved and can not be used" is displayed and application exits
*/

#include "mocks.h"


// Architectures //
// Connection decides how to as server, start as client
// Handshake - client, server
// Client
// Server
// UI - "me: ", input message, display message
// Sending, receiving

TEST(Cleanroom, StartAsServer)
{
    SocketWrapperMock socketMock;
    ISocketWrapperPtr socketPtr = nullptr;

    EXPECT_CALL(socketMock, Bind(_,_));
    EXPECT_CALL(socketMock, Listen());
    EXPECT_CALL(socketMock, Accept()).WillOnce(Return(std::make_shared<SocketWrapperMock>()));

    EXPECT_TRUE(utils::Connection(socketMock, socketPtr));
}

TEST(Cleanroom, StartAsClient)
{
    SocketWrapperMock socketMock;
    ISocketWrapperPtr socketPtr = nullptr;

    EXPECT_CALL(socketMock, Bind(_,_)).WillOnce(Throw(std::runtime_error("")));
    EXPECT_CALL(socketMock, Connect(_,_)).WillOnce(Return(std::make_shared<SocketWrapperMock>()));

    EXPECT_FALSE(utils::Connection(socketMock, socketPtr));
}

TEST(Cleanroom, ClientHandshake)
{
    SocketWrapperMock socketMock;
    ISocketWrapperPtr socketPtr = nullptr;
    std::shared_ptr<SocketWrapperMock> clientSocketMock = std::make_shared<SocketWrapperMock>();

    EXPECT_CALL(socketMock, Bind(_,_)).WillOnce(Throw(std::runtime_error("")));
    EXPECT_CALL(socketMock, Connect(_,_)).WillOnce(Return(clientSocketMock));
    EXPECT_CALL(*clientSocketMock.get(), Write(utils::GetClientHello())).Times(1);
    EXPECT_CALL(*clientSocketMock.get(), Read(_)).Times(1);

    EXPECT_FALSE(utils::Connection(socketMock, socketPtr));

    EXPECT_NE(nullptr, socketPtr);
}

TEST(Cleanroom, ServerHandshake)
{
    SocketWrapperMock socketMock;
    ISocketWrapperPtr socketPtr = nullptr;
    std::shared_ptr<SocketWrapperMock> serverSocketMock = std::make_shared<SocketWrapperMock>();

    {
        InSequence sequence;

        EXPECT_CALL(socketMock, Bind(_,_));
        EXPECT_CALL(socketMock, Listen());
        EXPECT_CALL(socketMock, Accept()).WillOnce(Return(serverSocketMock));
    }
    {
        InSequence sequence;

        EXPECT_CALL(*serverSocketMock.get(), Read(_)).Times(1);
        EXPECT_CALL(*serverSocketMock.get(), Write(utils::GetServerHello())).Times(1);
    }
    EXPECT_TRUE(utils::Connection(socketMock, socketPtr));

    EXPECT_NE(nullptr, socketPtr);
}

TEST(Cleanroom, ParseServerNickname)
{
    SocketWrapperMock socketMock;
    ISocketWrapperPtr socketPtr = nullptr;
    std::shared_ptr<SocketWrapperMock> clientSocketMock = std::make_shared<SocketWrapperMock>();

    ConnecionWrapper wrapper (socketMock);

    EXPECT_CALL(socketMock, Bind(_,_)).WillOnce(Throw(std::runtime_error("")));
    EXPECT_CALL(socketMock, Connect(_,_)).WillOnce(Return(clientSocketMock));
    EXPECT_CALL(*clientSocketMock.get(), Write(utils::GetClientHello())).Times(1);
    EXPECT_CALL(*clientSocketMock.get(), Read(_)).Times(1);

    EXPECT_FALSE(utils::Connection(socketMock, socketPtr));

    EXPECT_EQ(wrapper.getNickname(), "server");

    EXPECT_NE(nullptr, socketPtr);
}
