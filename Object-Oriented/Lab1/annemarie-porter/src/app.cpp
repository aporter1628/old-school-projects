#include <server.h>
#include <string>
#include <mymath.h>

using namespace ucm;

// Added a comment

int main(int argc, char** argv){

    Server server(argc, argv);

    server.renderHTML("/","index.html");

    server.route("/sayHello", [&](const request& req, response& res){
        res.sendHTML("Hello World");
    });

    server.route("/echo", [&](const request& req, response& res){
        if (req.has_params({"text"})){
            // Valid input
            std::string text = req.url_params.get("text");

            res.sendHTML(text);
        }
        else {
            // User has not provided a value for text
            res.sendError400();
        }
    });

   
    server.route("/sub", [&](const request& req, response& res){
        if (req.has_params({"x", "y"})){
            std::string x_string = req.url_params.get("x");
            std::string y_string = req.url_params.get("y");

            int x = std::stoi(x_string);
            int y = std::stoi(y_string);

            int ans = sub(x, y);


            json answer;
            answer["ans"] = ans;

            res.sendJSON(answer);
        }
        else {
            res.sendError400();
        }
    });

    server.route("/mult", [&](const request& req, response& res){
        if (req.has_params({"x", "y"})){
            std::string x_string = req.url_params.get("x");
            std::string y_string = req.url_params.get("y");

            int x = std::stoi(x_string);
            int y = std::stoi(y_string);

            int ans = mult(x, y);


            json answer;
            answer["ans"] = ans;

            res.sendJSON(answer);
        }
        else {
            res.sendError400();
        }
    });

    server.route("/div", [&](const request& req, response& res){
        if (req.has_params({"x", "y"})){
            std::string x_string = req.url_params.get("x");
            std::string y_string = req.url_params.get("y");

            int x = std::stoi(x_string);
            int y = std::stoi(y_string);

            int ans = divi(x, y);


            json answer;
            answer["ans"] = ans;

            res.sendJSON(answer);
        }
        else {
            res.sendError400();
        }
    });

    server.route("/add", [&](const request& req, response& res){
        if (req.has_params({"x", "y"})){
            std::string x_string = req.url_params.get("x");
            std::string y_string = req.url_params.get("y");

            int x = std::stoi(x_string);
            int y = std::stoi(y_string);

            int ans = add(x, y);


            json answer;
            answer["ans"] = ans;

            res.sendJSON(answer);
        }
        else {
            res.sendError400();
        }
    });

    server.run();
}
