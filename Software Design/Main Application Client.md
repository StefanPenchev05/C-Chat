``` mermaid

graph TD;
    A[Main Application] -->|Initialize| H[Client Initialization];
    A -->|Process Commands| C[Client Command];
    A -->|Network Handling| D[Client Network];
    A -->|Utility Functions| E[Client Utils];
    H -->|Connect to Server| I[Client Connection];
    I -->|Send Commands| C;
    I -->|Receive Responses| D;
    E -->|Helper Functions| C;
    E -->|Helper Functions| D;

    subgraph src
        H[Client Initialization]
        C[Client Command]
        D[Client Network]
        E[Client Utils]
        I[Client Connection]
    end
```
