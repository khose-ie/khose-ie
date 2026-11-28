---
name: "architecture-persistent-data"
description: "Architecture persistent data documentation for the [Product-Name] application."
version: "1.0"
created: "2024-06-05"
updated: "2024-06-05"
---

# Architecture Persistent Data Documentation

[This document describes architecture-level persistent data design, including databases, schemas, files, and data lifecycle.]
[It should be language-neutral and implementation-agnostic as much as possible.]



## Persistent Data Overview

[Describe what data must be persisted, why persistence is needed, and where data is stored.]
[Include data classification such as business data, system metadata, audit data, and configuration data.]



## Storage Topology

| Storage Name | Type | Scope | Primary Usage | Availability Requirement |
| :--- | :--- | :--- | :--- | :--- |
| [Storage-A] | [SQLite/PostgreSQL/File/Object Storage/etc.] | [Local/Remote/Hybrid] | [Usage] | [Offline/Online/Both] |



## Data Domain and Ownership

[Define the logical data domains and ownership boundaries.]

| Data Domain | Owner Module | Description | Upstream Producer | Downstream Consumer |
| :--- | :--- | :--- | :--- | :--- |
| [Domain-X] | [Module] | [Description] | [Producer] | [Consumer] |



## Logical Data Model

[Describe key entities and relationships at architecture level.]

| Entity | Key Fields | Relationship | Constraints |
| :--- | :--- | :--- | :--- |
| [Entity-A] | [id, ...] | [1:1 / 1:N / N:M with Entity-B] | [Unique/Not null/Reference rules] |



## Physical Schema and File Layout

[Describe the concrete schema/table/file layout.]



### Database Schema (if applicable)

| Table/Collection | Purpose | Primary Key | Indexes | Retention Policy |
| :--- | :--- | :--- | :--- | :--- |
| [table_x] | [Purpose] | [PK] | [Index list] | [Retention] |



### File-Based Storage (if applicable)

| Path Pattern | Format | Producer | Consumer | Rotation/Retention |
| :--- | :--- | :--- | :--- | :--- |
| [/path/to/file] | [JSON/YAML/TOML/Binary] | [Module] | [Module] | [Policy] |



## Data Access and Abstraction

[Describe repositories, gateways, and data access boundaries.]

| Access Interface | Used By | Backing Store | Transaction Boundary | Caching Policy |
| :--- | :--- | :--- | :--- | :--- |
| [Interface-X] | [Module] | [Store] | [Boundary] | [Policy] |



## Data Consistency and Transaction Strategy

[Describe consistency model and transaction guarantees.]

| Scenario | Consistency Requirement | Transaction Strategy | Conflict Handling |
| :--- | :--- | :--- | :--- |
| [Scenario] | [Strong/Eventual] | [Single store/Cross-store saga/etc.] | [Retry/Merge/Reject] |



## Data Lifecycle

[Describe creation, update, archival, and deletion lifecycle.]

| Data Type | Create Trigger | Update Trigger | Archive Strategy | Delete Strategy |
| :--- | :--- | :--- | :--- | :--- |
| [Type] | [Trigger] | [Trigger] | [Strategy] | [Strategy] |



## Migration and Versioning Strategy

[Describe schema evolution and backward compatibility strategy.]

| Change Type | Versioning Rule | Migration Method | Rollback Plan |
| :--- | :--- | :--- | :--- |
| [Add column/Change type/etc.] | [Rule] | [Method] | [Plan] |



## Security and Compliance for Persistent Data

[Describe data protection and compliance controls.]

| Security Topic | Requirement | Implementation |
| :--- | :--- | :--- |
| Data Classification | [Requirement] | [Implementation] |
| Encryption at Rest | [Requirement] | [Implementation] |
| Access Control | [Requirement] | [Implementation] |
| Sensitive Data Handling | [Requirement] | [Implementation] |



## Backup, Recovery, and Disaster Readiness

[Describe backup and recovery objectives and methods.]

| Store | Backup Method | Frequency | RPO | RTO | Recovery Verification |
| :--- | :--- | :--- | :--- | :--- | :--- |
| [Store] | [Method] | [Frequency] | [Target] | [Target] | [How verified] |



## Data Quality and Observability

[Describe how data quality and storage health are observed.]

| Signal | Description | Threshold/Expectation | Alerting |
| :--- | :--- | :--- | :--- |
| [Metric/Log/Event] | [Description] | [Value] | [Mechanism] |