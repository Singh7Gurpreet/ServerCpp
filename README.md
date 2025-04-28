# HTTP Web Server with Router and Strategy Pattern

This project implements a **high-performance HTTP web server** in C++ using layers of abstraction.  
It provides an **easy way to start different server types** (single-threaded, multi-threaded, event-based) and **handle routing** (`GET`, `POST`, `PUT`, `PATCH`) with clean API design.

---

## 🚀 Features

- Create different types of servers using `ServerFactory`:
  - **Single-threaded Server**
  - **Multi-threaded Server**
  - **Multi-threaded + Event-based Server** (🚧 under development for full stability)
- Easy-to-use **Router** to define request handlers.
- Abstraction layers for adding new server strategies in the future.

---

## 🛠️ Server Setup Example

```cpp
#include "Router.h"
#include "ServerFactory.h"

int main() {
    Router& router = Router::getRouter();

    router.get("/", [&](HttpRequest& req) {
        req.response.setBody("<h1>Hello World from layers of abstraction</h1>")
                    .setContentType(HttpContentType::APPLICATION_JSON)
                    .setStatus(HttpStatusCode::OK);
    });

    try {
        auto server = ServerFactory::create(ServerType::HTTP, ServerFlags::MULTITHREADED | ServerFlags::EVENTS_BASED);
        server->kickStart(3000, [&]() {
            std::cout << "Listening on port 3000...\n";
        });
    } catch (const std::exception& e) {
        std::cerr << "Server failed: " << e.what() << std::endl;
    }

    return 0;
}
```

---

## 🧩 Available Server Flags

You can customize the server behavior using these flags:

| Flag                | Description                                |
|---------------------|--------------------------------------------|
| `ServerFlags::MULTITHREADED` | Runs server using multiple threads. |
| `ServerFlags::EVENTS_BASED`  | Adds event-driven I/O handling (under development 🚧). |
| (No flag)           | Runs server in single-threaded mode.       |

👉 **You can combine flags** using the bitwise OR operator (`|`).

Example:
```cpp
ServerFlags::MULTITHREADED | ServerFlags::EVENTS_BASED
```

---

## 🛣️ How to Implement Router Functions

The `Router` class lets you **map HTTP methods and paths** to custom handlers easily.

Available methods:
- `router.get(path, handler)`
- `router.post(path, handler)`
- `router.put(path, handler)`
- `router.patch(path, handler)`

### Example Usage:

```cpp
Router& router = Router::getRouter();

router.get("/hello", [&](HttpRequest& req) {
    req.response.setBody("{\"message\":\"Hello, GET!\"}")
                .setContentType(HttpContentType::APPLICATION_JSON)
                .setStatus(HttpStatusCode::OK);
});

router.post("/submit", [&](HttpRequest& req) {
    req.response.setBody("{\"message\":\"Data received via POST\"}")
                .setContentType(HttpContentType::APPLICATION_JSON)
                .setStatus(HttpStatusCode::OK);
});
```

---

## 🧠 How Routing Internally Works

- `Router` uses a **singleton pattern** (`getRouter()`) so there's only one router instance.
- You can **register routes** based on HTTP method and path.
- When a client sends a request:
  1. **Router parses** the incoming HTTP request.
  2. **Finds the matching route** (method + path) in its internal `routesMap`.
  3. If found, the **corresponding handler is executed**.
  4. If not found, the router **responds with a `BAD_REQUEST (400)` error**.

### Behind the scenes:

```cpp
// Internally when you call router.get("/path", handler)
void Router::get(const std::string& path, RouteHandler handler) {
    route(HttpMethod::GET, path, handler);
}
```

If the route is not found:

```json
{
  "message": "Url not found"
}
```
is returned with HTTP `400 BAD_REQUEST` status.

---

## ⚙️ Server Creation Logic

The server creation is handled dynamically using `ServerFactory`:

```cpp
std::unique_ptr<Server> ServerFactory::create(ServerType type, int flag);
```

- If `MULTITHREADED` and `EVENTS_BASED` are set → creates an event-driven multi-threaded server.
- If only `MULTITHREADED` is set → creates a simple multi-threaded server.
- Else → creates a basic single-threaded server.

---

## ⚡ Important Notes

- **Events-based strategy is still under development.**  
  It may not be fully production-ready yet.
- Always **handle exceptions** during server startup to ensure clean error handling.
- You can easily extend this framework to add `DELETE` or custom HTTP methods.

---

## 📜 License

This project is licensed under the MIT License.

---
