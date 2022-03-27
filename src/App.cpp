#include <cstdio>
#include <sharpen/HttpServer.hpp>
#include <sharpen/Converter.hpp>
#include <sharpen/IpEndPoint.hpp>
#include <sharpen/CtrlHandler.hpp>

class SimpleHttpServer:public sharpen::HttpServer
{
private:
    using Self = SimpleHttpServer;

protected:
    virtual void OnNewMessage(sharpen::NetStreamChannelPtr channel,const sharpen::HttpRequest &req,sharpen::HttpResponse &res) override
    {
        const char msg[] = u8"关注嘉然,顿顿解馋";
        res.Body().CopyFrom(msg,sizeof(msg) - 1);
        res.Header()["Content-Length"].assign("25",2);
        res.Header()["Content-Type"] = "text/plain;charset=utf-8";
    }
public:

    SimpleHttpServer(sharpen::AddressFamily af,const sharpen::IEndPoint &endpoint,sharpen::EventEngine &engine)
        :HttpServer(af,endpoint,engine,"SimpleHttp")
    {}

    virtual ~SimpleHttpServer() noexcept = default;
};

static void StopServer(SimpleHttpServer *server)
{
    server->Stop();
}

static void Entry(sharpen::Uint16 port)
{
    sharpen::StartupNetSupport();
    try
    {
        sharpen::IpEndPoint ep{0,port};
        SimpleHttpServer server{sharpen::AddressFamily::Ip,ep,sharpen::EventEngine::GetEngine()};
        std::printf("now listen on %hu\nuse ctrl+c to stop\n",port);
        sharpen::RegisterCtrlHandler(sharpen::CtrlType::Interrupt,std::bind(&StopServer,&server));
        server.RunAsync();
        std::puts("server stop");
    }
    catch(const std::exception& e)
    {
        std::fprintf(stderr,"error[message = %s]\n",e.what());
    }
    sharpen::CleanupNetSupport();
}

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        std::puts("usage: <port> [thread number]");
        return 0;
    }
    sharpen::Size thrNum{std::thread::hardware_concurrency()};
    sharpen::Uint16 port{sharpen::Atoi<sharpen::Uint16>(argv[1],std::strlen(argv[1]))};
    if(argc > 2)
    {
        sharpen::Size tmp{sharpen::Atoi<sharpen::Size>(argv[2],std::strlen(argv[2]))};
        if(tmp)
        {
            thrNum = tmp;
        }
    }
    sharpen::EventEngine &eng = sharpen::EventEngine::SetupEngine(thrNum);
    eng.Startup(&Entry,port);
    return 0;
}