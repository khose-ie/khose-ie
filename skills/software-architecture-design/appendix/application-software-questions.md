# Application Software Questions

This document lists the question dimensions that should be asked to gather necessary information for designing the architecture of an application software system.

The whole checking points have been organized into different categories to ensure comprehensive coverage of all aspects of application software architecture design.



- [Background and Context](#background-and-context)
- [Software Architecture](#software-architecture)
- [Technology Stack](#technology-stack)
- [Layout and Module Design](#layout-and-module-design)
- [Non-Functional Requirements](#non-functional-requirements)



## Background and Context

For the background and context, consider the following questions.



- **Application Background**

  What is the purpose and context of the application? What problem does it solve?



- **Business Goals**

  What are the business objectives and goals that the application aims to achieve?



- **Target Audience and Scenario**

  Who are the intended users of the application? What are their characteristics and needs? In what scenarios will they use the application?



- **System Operational Logic**

  How is the system expected to operate? What are the key workflows and processes within the application?



- **Imaged High-Level Architecture**

  Does the human user have an expected high-level architecture in mind for the system? What are the key components and their interactions?



- **Existing Assets and Systems**

  Are there any existing systems, applications, or assets that the new application needs to integrate with or consider?



## Software Architecture

For the software architecture, consider the following questions.



- **Architectural Style**

  What architectural style or pattern is preferred or expected for the system?

  A. Monolithic desktop application: UI + business logic + data storage are all in the same process. Deployment is simple, but coupling is relatively tight. Suitable for tools, utilities, and simpler applications.

  B. Front-end/back-end separated (local multi-process): The UI process is separated from an independent backend service (which may be local or remote). Isolation is good and independent updates are allowed, but IPC complexity increases. Suitable for applications with heavy backend logic.

  C. Hybrid (e.g., Tauri/Electron style): A web frontend + a lightweight Rust/Node.js backend are packaged together. Strong cross-platform capability, with native capabilities as well. Suitable for most modern desktop applications.

  D. Plugin-based/modular architecture: A core system + dynamically loaded plugins, supporting hot-plugging. Suitable for IDE-like platforms or platforms that require high extensibility.

  E. Other/custom: Please describe.



- **Communication Style**

  How do different components of the system communicate with each other? Are there specific protocols, message formats, or communication patterns that should be used?

  Examples of communication styles include synchronous request-response (e.g., HTTP, gRPC), asynchronous messaging (e.g., message queues, event buses), shared memory, or direct function calls.



## Technology Stack

For the technology stack, consider the following questions.



- **Application and Platform Frameworks**

  What application frameworks, libraries, or platform-specific technologies are expected or preferred for the system?

  Examples include desktop frameworks (e.g., Electron, Tauri, Qt), mobile frameworks (e.g., Flutter, React Native), and platform-specific SDKs or libraries.



- **CLI Frameworks**

  What command-line interface frameworks, libraries are expected or preferred for the system?

  Examples include CLI parsing libraries (e.g., Cobra for Go, argparse for Python, clap for Rust), command dispatch frameworks, and terminal UI libraries.



- **Frontend Frameworks**

  What frontend frameworks, libraries are expected or preferred for the system?

  Examples include desktop frontend frameworks (e.g., Electron, Tauri, Flutter), and UI component libraries.



- **Backend Frameworks**

  What backend frameworks, libraries are expected or preferred for the system?

  Examples include desktop backend frameworks.



- **Communication Frameworks**

  What communication frameworks, libraries are expected or preferred for the system?

  Examples include HTTP clients and servers, gRPC libraries, message queue clients, and event bus libraries.




- **Database and Storage Technologies**

  What database and storage technologies are expected or preferred for the system?

  Examples include relational databases (e.g., SQLite), NoSQL databases (e.g., MongoDB, Cassandra), key-value stores (e.g., Redis).

  Examples include configuration file formats (e.g., JSON, YAML, TOML).



- **Target Platforms**

  What target platforms are expected or preferred for the system?

  Examples include operating systems (e.g., Windows, macOS, Linux), mobile platforms (e.g., iOS, Android).



- **Packaging and Installation**

  What packaging and installation tools are expected or preferred for the system?

  Examples include package managers (e.g., npm, pip, Maven), build tools (e.g., Webpack, Gradle), and installation frameworks (e.g., installers, containerization tools like Docker).



## Layout and Module Design



- **Layered Structure**

  How should the system's layered structure be organized? 

  Recommended to use 4 layers. View Layer -> Depiction Layer -> App Layer -> Core Layer -> Platform Layer.

  - **View Layer**: Handles the presentation and user interface.
  - **Depiction Layer**: Provide the depiction logic and data for view layer.
  - **App Layer**: Contains the application logic and orchestrates interactions between layers, includes plugins and extensions.
  - **Core Layer**: Encapsulates the core business logic and domain models.
  - **Platform Layer**: Deals with platform-specific implementations and integrations.



- **Core Module Identification**

  Based on the usage scenarios you provided, I have identified the following core functional modules: [list]. Please confirm, or suggest additions, deletions, modifications, or merges.




- **Cross-Module Communication**

  What communication method should be used between modules? 
  
  Recommended List.
  A. Direct function calls (tight coupling)
  B. Event bus (loose coupling)
  C. Message queue (asynchronous)
  D. Hybrid: direct calls within layers, events between layers
  E. Others




- **Frontend-to-Backend Communication**

  What communication method should be used between the frontend and backend?
  If the choiced framework has includes the communication methods (like Tauri), you may follow the framework's recommended approach.

  Recommended List.
  A. Web-based Technology: RESTful APIs (HTTP/HTTPS), GraphQL, WebSockets
  B. Direct function call
  C. FFI based on C-ABI
  D. Hybrid: direct calls for local modules, FFI for external modules
  E. Others



## Non-Functional Requirements



- **Performance Targets**
  What are the expected values for startup time, memory usage, and operation response time?



- **Offline Availability**
  Which features must be available offline? How should data be cached locally?



- **Update Strategy**
  How should the application be updated?
  
  A. Full reinstallation
  B. Incremental update
  C. Silent background update
  D. Manual download and installation



- **Observability**
  What level of logging, crash reporting, and performance monitoring is required?
  
  A. Minimal (console logs only)
  B. Log files persisted to disk
  C. Crash reporting service
  D. Full telemetry



- **Internationalization (i18n)**
  Is multilingual support required? If so, how should translation files be managed?

