---
id: "[function-id]"
name: "Function Name" # A very short summary of the function, e.g., "Delete Order"
description: "[Short description of the function]"
submitter: "[submitter name, optional]"
status: "backlog"  # optional values: backlog, implemented, outdated
---

# [FUNCTION-ID] - [Feature Category]: [Function Name]



**Summary**
[Describe the core objective in a very short and unambiguous sentence to let people quickly understand the purpose.]



**Description**
[Provide a detailed description of the function, including its background (if have), purpose (if have), scope, and any relevant context.]
[If the description includes some content with a parallel relationship, please use a list to enumerate them.]



## Definitions (Optional)
[Provide detail information for the definitions if the requirement has created new one, such as UI statement, error codes.]
[The domain-specific terminology is not in the scope of this section.]



## Functional Cases

[Describe the functional use cases in detail.]

> [!important]
> Use cases are intended solely as references for requirement scenarios and do not define or limit the full scope of testing.

| ID   | Use Case                                 | Description                  |
| ---- | ---------------------------------------- | ---------------------------- |
| 01   | [[Action Name]](#CASE-01: [Action Name]) | Short description of CASE-01 |
| 02   | [[Action Name]](#CASE-02: [Action Name]) | Short description of CASE-02 |



### CASE-01: [Action Name]

[Provide a brief overview of the use case.]



**Conditions**:  
[Precise conditions that trigger this action, for example the system should in some state.]



**Normal Flow**:
1. [Step one]
2. [Step two]
3. ...



**Exceptional Flows**:

- **When [Condition A, e.g., out of stock]** → 

    [System reaction, e.g., rollback transaction, return message xxx]



- **When [Condition B, e.g., user banned]** → 

    [System reaction]



**Constraints**:
- **Concurrency**: Use optimistic locking; on update failure show "Data has been modified, please refresh and retry"



### CASE-02: [Next Action Name]
(Repeat the same structure)



## Performance and Stabilities

[Provide the performance and stability requirements for the function.]
[A specification could only include the functional cases requirements and don't inlcude a performance and stability requirements, in that case this section can be omitted.]




- **Performance**: Response time < 500ms (P95)
- **Performance**: Throughput > 1000 req/s



## Security and Scalability

[Provide the security and scalability requirements for the function.]
[A specification could only include the functional cases requirements and don't include security and scalability requirements, in that case this section can be omitted.]



- **Security**: Role checks required: `[Admin / Normal User / Specific Permission Code]`
- **Scalability**: [Add specific requirements if any]



## Appendix - Decision Records

[Store all selected-choice answers the user confirmed during the clarification stage (S3 and S4) for traceability.]



- Q: [Question 1]  
  A: [User's confirmed answer]



- Q: [Question 2]  
  A: [User's confirmed answer]
