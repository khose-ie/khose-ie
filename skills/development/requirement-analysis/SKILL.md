---
name: requirement-analysis
description: "Use for analyzing requirements. When the user submits a requirement, the skill will analyze it with multiple loops to clarify the details of the requirement by asking questions to the user. And then, the skill will generate a requirement analysis document in Markdown format."
user-invocable: true
---

# Requirement Analysis

This skill is designed to assist in analyzing requirements. When a user submits a requirement, the skill will engage in multiple loops of questioning to clarify the details of the requirement. After gathering sufficient information, the skill will generate a comprehensive requirement analysis document in Markdown format.



## Goal

The goal of this skill is to clearly understand the user's requirement by asking looped questions and produce a structured Markdown document that captures all relevant details.



## Mandatory State Machine Flow Rules (Must Follow Strictly)

You must operate in a loop across the following four states and are forbidden from skipping states:

- State S1 (Collect): Receive the user's raw verbal input and extract the core actions and objects.
- State S2 (Question): Based on three dimensions (Action / Reaction / Boundary), list ambiguous points and ask the user numbered follow-up questions. Absolutely do not output any XML tags during this stage.
- State S3 (Confirm): After the user answers, compile a "Confirmed Decisions Summary" for the user to review and confirm.
- State S4 (Generate): Only when the user explicitly inputs commands such as "confirm generate", "yes", or "OK" is the final Markdown document unlocked for output.


## Three-dimensional Clarification Logic (Checklist)

In S2 you must, for each extracted core action, iterate through the three dimensions below and ask questions. If the user answers "anything/whatever", you must provide concrete A/B options to force a selection.


**Dimension A: Action Triggering and Causality (Action)**

- Is this operation synchronous (waits for a result in real time) or asynchronous (puts a message on a queue / background job)?
- If a user triggers the action repeatedly (e.g., double-clicks a button), should the system be idempotent and ignore the second trigger, return an "operation too frequent" error, or perform the action twice?


**Dimension B: Reaction Paths and Side Effects (Reaction)**

- Success path: What are the core fields returned to the frontend on success? (For example: only an ID, or the full detail payload?)
- Failure path: On validation failure, should the service return HTTP 200 with business error codes, or raise an HTTP 4xx error?
- Side effects: Does the operation need to coordinate other modules? (For example: placing an order must decrement stock, send messages, write logs. Are these strong transactional guarantees or eventual consistency?)


**Dimension C: Boundaries and Constraints (Boundary)**

- Data boundaries: For text fields, what is the maximum length? For numeric fields, what are min/max values? What does null/empty mean?
- State boundaries: In which object states is the operation allowed or disallowed? (For example: can an order in "Cancelled" state be "Confirm Received"?)
- Concurrency boundaries: When multiple people operate on the same data concurrently, use optimistic locking (version), pessimistic locking (row lock), or last-writer-wins?


## Output Specification (Markdown Section Definition)

When you reach S4, you must output the Markdown file strictly following this example format. Crucially: include the choices the user confirmed in S3 in the **Decision Records** section.
If the user specified a path and filename for the output file, save it directly. If they did not, ask: "Where would you like the Markdown file saved? Please provide a full path and filename."

```markdown
---
id: "[FUNCTION]-[ID]"
jira_id: "JIRA-001"
author: "[author name, optional]"
status: "backlog"  # optional values: backlog, implemented, outdated
---

# Requirement Specification


## Summary

**Core Overview**:  
Describe the core objective in one unambiguous sentence.

**Detailed Description**:  
Write a paragraph describing background, goals, scope, and constraints for traceability.



## Decision Records

> Store all selected-choice answers the user confirmed during the clarification stage (S3) for traceability.

| Question | Decision |
| :--- | :--- |
| Concurrency strategy | Optimistic locking (version-based) |
| Failure return mode | HTTP 200 + unified business error code |
| ... | ... |


## Functional Requirements

### UC-01: [Action Name]

**Trigger Conditions**:  
[Precise conditions that trigger this action]

**Normal Flow**:
1. [Step one]
2. [Step two]
3. ...

**Exceptional / Alternative Flows**:
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
```


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

If in S2 the user says "use the generic/default option", you must reply: "To avoid ambiguity during the implementation phase, I cannot use the term 'generic' for now; please choose a default value from the options I list."
Terminator: Only when the user says "confirm generate" or "generate Markdown as is" are you allowed to output the Markdown file.

