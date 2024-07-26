``` mermaid

classDiagram
    class Main {
        +int main(int argc, char *argv[])
    }
    
    class Server {
        +void serverInit(int port)
        +void clientInit(int port)
    }

    class User {
        +char username[50]
        +char passwordHashed[256]
        +char email[100]
        +time_t created_at
        +void createUser(const char *username, const char *password, const char *email)
    }
    
    class DB {
        +void load_env(const char *filename)
        +void init_db()
        +MYSQL* connect_db()
        +void close_db(MYSQL *conn)
    }
    
    class MYSQL {
    }

    class UsersTable {
        +int user_id
        +VARCHAR username
        +VARCHAR password_hash
        +VARCHAR email
        +TIMESTAMP created_at
    }

    Main --> Server : controls
    Server --> User : manages
    Server --> DB : uses
    User --> DB : uses
    DB --> MYSQL : manages connection
    User .. UsersTable : stores data in
```

