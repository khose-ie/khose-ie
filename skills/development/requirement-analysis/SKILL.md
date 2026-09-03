---
name: requirement-analysis
description: "Use for analyzing requirements. When the user submits a requirement, the skill will analyze it with multiple loops to clarify the details of the requirement by asking questions to the user. And then, the skill will generate a requirement analysis document in Markdown format."
user-invocable: true
metadata:
  version: v1
  author: "khose-ie"
---

# Requirement Analysis

This skill is designed to assist in analyzing requirements. When a user submits a requirement, the skill will engage in multiple loops of questioning to clarify the details of the requirement. After gathering sufficient information, the skill will generate a comprehensive requirement analysis document in Markdown format.



## Basic Guidelines

- For all Q&A in this Skill, interactive components (such as checkboxes and dropdown menus) should be used preferentially for posing questions; if the platform does not support them, use clear numbered lists in the chat to ask questions.
- When the user explicitly answers “no other questions” or “proceed to the next step,” the AI must not continue to probe further and must move on to the next step (to avoid infinite loops). However, if new points raised by the user during the current discussion have not yet reached consensus, the AI must first return to those points and continue the discussion until all raised points have been confirmed; only then may it proceed to the next step.



## Goal

The goal of this skill is to clearly understand the user's requirement by asking looped questions and produce a structured Markdown document that captures all relevant details.



## Mandatory State Machine Flow Rules (Must Follow Strictly)

You must operate in a loop across the following 5 states and are forbidden from skipping states:

- State S1 (Collect): Receive the user's raw verbal input and extract the core actions and objects.
- State S2 (Question): Based on three dimensions (Action / Reaction / Boundary), list ambiguous points and ask the user numbered follow-up questions.
- State S3 (Discuss): Base on the information from S1, S2 and some additional data that the user provided, give some opinions and suggestions of you to improve the requirements. List all your suggestions and wait for the feedback of user.
- State S4 (Confirm): After the user answers and feedback, compile a draft version of the requirements to let the user review. (The draft version don't need to includes all content of the output, only need the summary, description and the index table of use cases.)
- State S5 (Generate): Only when the user explicitly inputs commands such as "confirm generate", "yes", or "OK" is the final Markdown document unlocked for output.



If the overall project background or basic product information cannot be found before entering S1, or if the relevant information is insufficient, you need to enter the S0 phase first:

- State S0 (Confirm basic product information): Ask the user to provide the project's basic information, including background (why this is being done), product information (what they want to build), target use cases (with examples), necessary system operation logic and high-level architecture, and the path to the general description document (if any). If the user does not provide this information, proactively follow up. After confirmation, if there is no document path, ask the user whether they need to create a new general product information document and have them specify the path and file name.

## Three-dimensional Clarification Logic (Checklist)

In S2 you must, for each extracted core action, iterate through the three dimensions below and ask questions. If the user answers "anything/whatever", you must provide concrete A/B options to force a selection.



**Dimension A: Action Triggering and Causality (Action)**

- Is this operation synchronous (waits for a result in real time) or asynchronous (puts a message on a queue / background job)?
- If a user triggers the action repeatedly (e.g., double-clicks a button), should the system be idempotent and ignore the second trigger, return an "operation too frequent" error, or perform the action twice?
- What's the conditions for enable/disable of these actions? If there are some related configurations for this action, what's the entrance, items and default values of these configurations.
- What's the conditions to trigger this action: in which object states is the operation allowed or disallowed? (For example: can an order in "cancelled" state be "Confirm Received"?)


**Dimension B: Reaction Paths and Side Effects (Reaction)**

- Success path: What are the core fields returned to the frontend on success? (For example: only an ID, or the full detail payload?)
- Failure path: On validation failure, should the service return HTTP 200 with business error codes, or raise an HTTP 4xx error?
- Side effects: Does the operation need to coordinate other modules? (For example: placing an order must decrement stock, send messages, write logs. Are these strong transactional guarantees or eventual consistency?)



**Dimension C: Boundaries and Constraints (Boundary)**

- Data boundaries: For text fields, what is the maximum length? For numeric fields, what are min/max values? What does null/empty mean?
- State boundaries: In which object states is the operation allowed or disallowed? (For example: can an order in "Cancelled" state be "Confirm Received"?)
- Concurrency boundaries: When multiple people operate on the same data concurrently, use optimistic locking (version), pessimistic locking (row lock), or last-writer-wins?



## Output Specification (Markdown Section Definition)

When you reach S5, you must output the Markdown file strictly following this example format. Crucially: include the choices the user confirmed in S3 and S4 in the **Decision Records** section.

- If the user specified a path and filename for the output file, save it directly. If they did not, ask: "Where would you like the Markdown file saved? Please provide a full path and filename."
- Don't write repeated information in chapter **Constraints**, if the same information has been described in above content, do not say it again. For example: If the content has already recorded "all pages except debug pages are limited to be modified", don't repeat it in the Constraints section, such as "scope: all pages except debug pages are limited to be modified; exception: debug pages".



````markdown
---
id: "[FUNCTION]-[ID]"
name: "Function Name" # A very short summary of the function, e.g., "Delete Order"
jira_id: "JIRA-001"
author: "[author name, optional]"
status: "backlog"  # optional values: backlog, implemented, outdated
---

# [requirement id] - [requirement name]



## Introduction

**Summary**:  
[Describe the core objective in one unambiguous sentence, a very short sentence.]



**Description**:  
[Write a paragraph describing background, goals, scope, and constraints for traceability.]
[If the description includes some content with a parallel relationship, please use a list to enumerate them.]



**Definitions** (Optional)
[Write some specific definitions here if there is, such as the data type, data length, UI statement, selections, etc..]



## Functional Requirements



| ID | Use Case |
| -- | -------- |
| UC-01 | [Action Name](#UC-01: [Action Name]) |
| UC-02 | [Action Name](#UC-02: [Action Name]) |



### UC-01: [Action Name]



**Trigger Conditions**:  
[Precise conditions that trigger this action]



**Normal Flow**:
1. [Step one]
2. [Step two]
3. ...



**Exceptional Flows**:
- **When [Condition A, e.g., out of stock]** → [System reaction, e.g., rollback transaction, return message xxx]
- **When [Condition B, e.g., user banned]** → [System reaction]



**Constraints**:
- **Data length**: FieldA: `VARCHAR(50)`
- **State machine**: Allowed states: `[Pending Payment, Pending Shipment]`; Disallowed states: `[Cancelled, Completed]`
- **Concurrency**: Use optimistic locking; on update failure show "Data has been modified, please refresh and retry"



### UC-02: [Next Action Name]
(Repeat the same structure)


## Non-Functional Requirements

- **Performance**: Response time < 500ms (P95)
- **Performance**: Throughput > 1000 req/s
- **Security**: Role checks required: `[Admin / Normal User / Specific Permission Code]`
- **Scalability**: [Add specific requirements if any]



## Appendix (Optional)
- **Glossary**: [Definitions of key business terms]
- **References**: [Prototype link / PRD link]



## Appendix - Decision Records

[Store all selected-choice answers the user confirmed during the clarification stage (S3 and S4) for traceability.]

- Q: [Question 1]  
  A: [User's confirmed answer]
- Q: [Question 2]  
  A: [User's confirmed answer]

````


## Appendix: System Predefined "Common Missing Boundaries" Checklist (Must Proactively Check)

When asking questions, you must subconsciously apply the following checklist to the current business. If applicable, ask; otherwise, ignore:

- Lists/pagination: Ask default page size (e.g., 10/20/50)? Sorting field and direction?
- Amounts/prices: Ask currency unit (yuan/cents/milli)? Decimal rounding rules (round half up / bankers' rounding)?
- Deletion: Ask whether deletion is physical (DB record removed) or logical (mark is_deleted=1)?
- Files/images: Ask maximum allowed file size? Permitted file extensions? Retry strategy for upload failures?
- State transitions: Draw or enumerate state transition graphs (A->B allowed, but is C->A allowed?).


## Appendix: Negative and Positive Example Prompts (For AI Reference)

**Bad Example (poor question):**

"Do you have any other requirements for this feature?" (Too vague for the user to answer)


**Good Example (effective question):**

For the "delete order" feature you mentioned, I have identified three boundary questions that must be confirmed; please choose:

1. Data cleanup boundary: Is deletion physical (record removed from DB) or logical (mark as deleted and keep data)?
2. State boundary: If the order is in "Shipped" state, is deletion allowed? If allowed, must a "return" flow be triggered first?
3. Concurrency boundary: If an admin is editing the order at the moment of deletion, should the system reject with an error or force overwrite?


## Appendix: Special Instructions (Prevent AI Hallucination)

- Terminator: Only when the user says "confirm generate" or "generate Markdown as is" are you allowed to output the Markdown file.
- If in S2 the user says "use the generic/default option", you must reply: "To avoid ambiguity during the implementation phase, I cannot use the term 'generic' for now; please choose a default value from the options I list."
- If the user indicates that a certain topic belongs to a different requirement or is outside the current scope, do not record any "out of scope" notes in the Markdown output. Only include information that is within the current requirement's scope.

