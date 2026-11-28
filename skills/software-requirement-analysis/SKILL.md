---
name: software-requirement-analysis
description: >
  This skill covers the techniques and practices for analyzing software requirements effectively and is applicable to embedded software, desktop applications and web applications.
  AI should follow this skill to ask question to the user to clarify details and give the detailed requirement specification and generate multiple requirement specification documents after the user approves.
license: MIT
metadata: 
    version: 1.0.0
    author: Khose-ie<khose-ie@outlook.com>
---

# Software Requirement Analysis Skill

This skill provides guidance on how to effectively analyze software requirements, ensuring that all necessary details are captured and documented. It helps AI to interact with users to clarify requirements, produce detailed requirement specifications, and generate multiple requirement specification documents for user approval.

The skill defineds a multiple-round of question and answer loop to collect all necessary information, discuss ambiguities and conflicts, and at last output a series of documents in Markdown.


There are some basic principles for the skill itself and we list them here.

- **Human Decision**: The AI shall not make any decisions in architecture design. Every decision must be made by the human user, the AI could only provide suggestions and recommendations.

- **Iterative Process**: The AI shall follow an iterative process of questioning, discussion, and refinement to ensure that all aspects of the architecture are thoroughly considered and agreed upon by the human user.

- **Checkpoints**: Every step could not be continued to push unless all points have been checked and there is an agreement between the AI and the human user. Otherwise the human user confirm to continue without the agreement.



## Goals

This skill is going to analysis the requirements that inputed by the human user and make a clear, unambiguous, well-defined, and thoughtful specifications and generate the documentation in Markdown format.



## Mandatory Stages

You must operate in a loop across the following 5 states and are forbidden from skipping states:

- **Stage S0: Background**

  Ask the user to provide the project's basic information, including background (why this is being done), product information (what they want to build), target use cases (with examples), necessary system operation logic and high-level architecture.

  If the user does not provide this information, proactively follow up.
  If there is somewhere that record these information that you can find it, skip this stage.
  

- **Stage S1: Idea Collection**

  Collect the user's raw thoughts, small ideas, and mental images about the intended software; expect early, incomplete, or vague input. Extract core actions, objects, goals, constraints, and open questions; ask clarifying questions until the idea and scope are clear enough to proceed.


- **Stage S2: Question**

  Ask detailed questions to resolve S1 ambiguities and gaps; confirm three dimensions (Action / Reaction / Boundary) are complete and accurate before making the specification.

  Prefer interactive components (checkboxes, dropdowns), else a numbered list. 
  Proceed only after all questions are resolved and the user confirms the information is sufficient.

  Question Reference: 
  [`common-requirement-questions.md`](./appendix/common-requirement-questions.md)



- **Stage S3: Discussion**

  Base on the information from S1, S2 and some additional data that the user provided, give some opinions and suggestions of you to improve the requirements. List all your suggestions and wait for the feedback of user.



- **State S4: Confirmation**

  Summarize the final specification and ask the user to review and confirm it meets the requirements and constraints. Do not proceed without explicit user confirmation.



- **Stage S5: Generation**

  Produce the final requirement specification documents.

  All decision questions which be asked in S2 shall be recorded in the last of the generated document for traceability, typically under an "Appendix - Decision Records" section.



## Documentations

Every requirement will be generated to one specification and be documented in a dedicated file following the provided template.

The documentation should include all functional and non-functional requirements, use cases, and decision records for traceability.


### Specification Documentation

The specification documentation should follow the template and include all relevant sections such as functional requirements, non-functional requirements, use cases, and decision records for traceability.

The specification documentation should be put in the sub path which corresponds to the feature category of the requirement.
For example, we have a feature category named "order-management", and we have a function specification named "delete-order". The specification documentation for a requirement under this category should be placed in `./docs/specifications/order-management` and the file name should be the `req-001-delete-order.md`.
The `req-001` is the ID of the function specification, it could be a local identifier of this repository, it could also be an UUID from other system like Jira.


- **File:** `[id]-[function-name].md`
- **Path:** `./docs/specifications/[feature-category-name]`
- **Template:** `./templates/ex-001-example-function-name.template.md`
