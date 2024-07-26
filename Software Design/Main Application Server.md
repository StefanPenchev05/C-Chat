```mermaid
graph TD;
    A[Main Application] -->|Initialize| B[Server Initialization];
    A -->|Process Commands| C[Server Command];
    A -->|Network Handling| D[Server Network];
    A -->|Utility Functions| E[Server Utils];
    B -->|Configure Network| D;
    B -->|Setup Commands| C;
    D -->|Accept Connections| F[Client Connections];
    C -->|Execute Command| G[Specific Command];
    E -->|Helper Functions| C;
    E -->|Helper Functions| D;

    subgraph src
        B[Server Initialization]
        C[Server Command]
        D[Server Network]
        E[Server Utils]
        F[Client Connections]
        G[Specific Command]
    end
  ```
