---
name: software-architecture-design
description: >
    This skill defines the principles and process for designing software architecture and is applicable to both embedded firmware and application software.
    AI should follow this skill to ask question to the user to clarify details and give the architecture design and generate one or more architecture design documents after the user approves.
license: MIT
metadata: 
    version: 1.0.0
    author: Khose-ie<khose-ie@outlook.com>
---

# Software Architecture Design Skill

This skill defines the principles and process for designing software architecture and guides AI in interacting with users to clarify requirements, provide architecture designs, and generate architecture design documents upon user approval.

The software architecture focus on the high-level system structure includes system overview, decision of technical stacks/solutions, levels and boundaries of components and the communication between them, applicable to both embedded firmware and application software.

The skill defineds a multiple-round of question and answer loop to collect all necessary information, discuss design options, and at last output a series of documents in Markdown.



There are some basic principles for the skill itself and we list them here.



- **Human Decision**: The AI shall not make any decisions in architecture design. Every decision must be made by the human user, the AI could only provide suggestions and recommendations.

- **Iterative Process**: The AI shall follow an iterative process of questioning, discussion, and refinement to ensure that all aspects of the architecture are thoroughly considered and agreed upon by the human user.

- **Checkpoints**: Every step could not be continued to push unless all points have been checked and there is an agreement between the AI and the human user. Otherwise the human user confirm to continue without the agreement.



## Goals

The skill is going to make a clear, determined, and well-structured architecture design and generate several documents.

These architecture documents will be the **constitution** of the entire software, all subsequent function level or module level design must be aligned with them.



These documents should clarify below points.

- **Background and Motivation**: What problem does the application solve, who are the target users, and what scenarios does it cover.

- **Architecture Style**: The selected architectural pattern (for example, for desktop application, it will be monolithic desktop, front-end and back-end separation, hybrid, plugin-based, etc.).

- **Main Technology Stack**: Selected programming languages, frameworks, communication protocols, storage solutions, and build-packaging tools.

- **Layered Architecture**: High-level layers (for example, for desktop application, it will be Presentation Layer → Application Layer → Domain Layer → Infrastructure Layer) and their respective responsibilities.

- **Module Communication**: How modules within the system interact with each other (direct invocation, event bus, message queue, IPC).

- **Non-functional requirements**: Performance, security, observability, update strategies, and other quality attributes.



## Mandatory Stages

The software architecture design must follow several mandatory stages, can not skip.
When AI completes each stage, it should summarize the findings and confirm with the human user before proceeding to the next stage.



- **Stage S1: Collection**

  Collect architecture-design context: background, main functions, user scenarios, proposed architecture, core operation logic, and constraints. Extract core actions/objects; ask clarifying questions until requirements are clear.



- **Stage S2: Clarification**

  Ask detailed questions to resolve S1 ambiguities and gaps; confirm requirements, constraints, and context are complete and accurate before design.

  Prefer interactive components (checkboxes, dropdowns), else a numbered list. 
  Proceed only after all questions are resolved and the user confirms the information is sufficient.

  Question Reference: 
  [`embedded-firmware-questions.md`](./appendix/embedded-firmware-questions.md) for embedded firmware; 
  [`application-software-questions.md`](./appendix/application-software-questions.md) for application software.



- **Stage S3: Design and Discussion**

  Create an initial architecture design from S1–S2 inputs; present key decisions, trade-offs, and rationale. Discuss with the user, incorporate feedback, and refine the design to meet requirements and constraints.


- **Stage S4: Confirmation**

  Summarize the final architecture design: key decisions, trade-offs, and rationale. Ask the user to review and confirm it meets requirements and constraints. Do not proceed without explicit user confirmation.



- **Stage S5: Generation**

  Produce the final architecture documents.



## Documentations

The architecture design will be documented in several files, each serving a specific purpose.
Please understand the purpose of each document and generate them following the provided templates.



### Architecture Documentation

The architecture document provides a comprehensive design of the system's architecture, including its structure, components, interactions, and design rationale. It serves as a reference for both the development team and stakeholders to understand the architectural decisions and their implications.



- **File:** `architecture.md`
- **Path:** `./docs/design`
- **Template:** `./templates/architecture.template.md`



### Communication Documentation

The communication document provides the common used communication methods, protocols, and patterns within the system. It helps the development team and stakeholders understand how different components interact and exchange information.



- **File:** `architecture-communication.md`
- **Path:** `./docs/design`
- **Template:** `./templates/architecture-communication.template.md`



The communication document should cover all types of common communication within the system, includes but not limited to below.

- **Terminal-Cross Communication**, such as front-end/back-end communication in application software or inter-board communication in embedded software.

- **Common Communication within a System**, such as RESTful, gRPC, or microservices in application software, and signals, message queues, event buses, etc. in embedded software.

- **Communication with Third-Party Services**, such as calling external APIs or integrating third-party systems.



The document must clearly describe below points of each communication method, protocol, or pattern used within the system.

- Communication Overview (describes the overall architecture and flow of communication).
- Communication Protocols (describes the protocols used and their configurations).
- Interface Signatures (if applicable, describes interface names, parameters, return values, and their constraints; interfaces may be functions or other styles of APIs).
- Message/Event Definitions (including fields, types, and constraints).
- Error Handling (describes the error handling mechanisms in communication).
- Security (describes security measures for communication, such as encryption and authentication).
- Performance (describes performance requirements and optimization measures for communication).
- Scalability (describes the scalability of the communication solution and its ability to adapt to future needs).
- Maintainability (describes the maintainability of the communication solution, including the ability to facilitate debugging, monitoring, and upgrading).



### Definition Documentation

The definition document provides detailed definitions of the system's components, interfaces, and data structures. It serves as a reference for the development team to understand the precise specifications and constraints of each element within the architecture.



- **File:** `architecture-definition.md`
- **Path:** `./docs/design`
- **Template:** `./templates/architecture-definition.template.md`



### Configuration Documentation

The configuration document provides detailed information about the system's configuration settings, including environment variables, compiling options, and system parameters. It serves as a reference for the development team to understand how the system is configured and how different components interact through configuration.



- **File:** `architecture-configuration.md`
- **Path:** `./docs/design`
- **Template:** `./templates/architecture-configuration.template.md`



### Persistent Data Documentation

The persistent data document provides detailed information about the system's persistent data storage, including databases, schemas, tables, and data models. It serves as a reference for the development team to understand how data is structured, stored, and accessed within the system.

The persistent data document includes the application configuration files and databases.



- **File:** `architecture-persistent-data.md`
- **Path:** `./docs/design`
- **Template:** `./templates/architecture-persistent-data.template.md`



### Module Design Documentation

The module design document provides detailed information about the design of individual modules within the system, including their responsibilities, interfaces, and interactions with other modules.

It serves as a reference for the development team to understand how each module is structured and how it contributes to the overall architecture.



- **File:** `module-design-<module-name>.md`
- **Path:** `./docs/design/<module-name>`
- **Template:** `./templates/architecture-module-design.template.md`



### Decision Record Documentation

The decision record document records all architecture decisions reached during the communication phase, including the reasons for the decisions and alternative options. It also captures any changes in the architecture design during subsequent feature design.



- **File:** `architecture-decision-record.md`
- **Path:** `./docs/design`
- **Template:** `./templates/architecture-decision-record.template.md`



## Mandatory Architectural Constraints (Locks)

| Lock Name                         | Constraint Description                                       |
| --------------------------------- | ------------------------------------------------------------ |
| Architecture Style Lock           | Once the architectural style is determined, all subsequent functional designs must follow that style. AI must not introduce new architectural patterns without authorization during implementation (for example, suddenly adding microservices to a monolithic application). |
| Technology Stack Lock             | Once the technology stack is determined, no new languages or frameworks may be arbitrarily added to core components unless the discussion returns to S3 and user consent is obtained. |
| Layered Dependency Direction Lock | The dependency direction must point from the outer layers to the inner layers (Presentation Layer → Application Layer → Domain Layer → Infrastructure Layer). Inner layers (Domain Layer) must not depend on outer layers. |
| Communication Protocol Lock       | Once the cross-module communication method is determined, all newly added modules must use the same pattern. There must not be a chaotic situation where "some modules use an event bus while others use direct calls." |
| Data Storage Abstraction Lock     | The concrete implementation of data storage (for example, SQLite or files) must be hidden from upper layers, and upper layers must depend on abstract interfaces (Repository pattern). |
| Unified Error Handling Lock       | The entire system must use a unified error handling pattern (for example, uniformly use Result<T, E> or a unified error type), and different modules must not adopt widely divergent error handling styles. |



