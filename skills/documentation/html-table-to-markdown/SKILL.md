---
name: html-table-to-markdown
description: "Use when converting HTML tables in Markdown documentation to Markdown pipe tables, especially OCPP documentation tables that contain description rows, colspan, or rowspan. Preserve source wording and validate that no HTML table tags remain."
user-invocable: true
metadata: 
  version: v1
  author: "khose-ie"
---

# HTML Table To Markdown

Convert HTML tables embedded in Markdown documents into Markdown pipe tables. Intended for technical documentation where original wording must be preserved.

## Scope

- When the user requests converting HTML tables in a file or within a specified range to Markdown pipe tables.
- Tables may include `<table>`, `<tr>`, `<td>`, `colspan`, or `rowspan` attributes.
- Files can be large; process in batches when necessary to avoid huge patches.

## Constraints

- Only alter table structure; do not change cell text, order, punctuation, capitalization, spacing, spelling mistakes, or unusual hyphenation.
- Do not run scripts or open a browser.
- Do not fix copy or formatting issues unrelated to table conversion.
- Do not merge separate tables incorrectly into one table.
- Preserve empty cells.
- If a cell contains the Markdown pipe `|`, escape it only as needed to maintain valid Markdown table structure; do not rewrite visible copy.
- Preserve HTML entities (e.g., `&amp;`) exactly as in the source unless the user explicitly asks for decoding.

## Conversion Procedure

1. Identify the target file and the conversion range.
2. Read surrounding context of each target table to determine header rows, column count, description rows, and any special merged cells.
3. Record a conversion baseline search for HTML table tags:

   ```text
   <table>|</table>|<tr>|</tr>|<td>|</td>
   ```

4. For large files, process tables in batches by adjacent sections so each patch contains a limited number of complete tables and avoids truncation.
5. For each table apply the following rules:
   - Remove `<table>` and `</table>`.
   - Remove each `<tr>` and `</tr>` tag.
   - Remove each `<td>` and `</td>` tag.
   - Treat the first row as the Markdown header row in most cases, followed immediately by a separator row, for example:

     ```markdown
     | Variable | Type | Description |
     | --- | --- | --- |
     ```

   - Convert each data row to a Markdown pipe row.
   - Preserve original column order and empty cells.
6. For tables that include the two leading description rows, apply the following:
   - Detect two consecutive rows like:

     ```html
     <tr><td colspan="N">Description</td></tr>
     <tr><td colspan="N">Description body</td></tr>
     ```

   - Remove these two rows from the Markdown table.
   - Place the second row (the description body) before the table using the format:

     ```text
     Description: <description body>
     ```

   - Leave one blank line between the description text and the Markdown table.
   - Preserve the description body verbatim.
7. For tables that contain a colspan-only row (a row with `colspan` that spans the whole table):
    - Treat the colspan row as a grouping title and do not keep it as a Markdown table row.
    - Close the preceding Markdown table before the colspan row.
    - Convert the colspan row text to bold plain text using `**<colspan row text>**`.
    - Keep two blank lines between the bold text and the preceding table, and one blank line between the bold text and the following table.
    - After the bold text, start a new Markdown table using the original table's header row as the new header, and use the next row as the first data row of the new table.
    - If several colspan rows appear in sequence, split the table for each colspan row following the same rules.
    - Do not discard any text from colspan rows. Example:

       ```markdown
       | Variable | Unit | Value |
       | --- | --- | --- |
       | Available | boolean | true |


       **Protocol and static vehicle information**

       | Variable | Unit | Value |
       | --- | --- | --- |
       | VehicleId | string | ... |
       ```
    - `rowspan` does not trigger table-splitting; keep content aligned with the original column count and fill affected positions with empty cells where necessary.
8. After each batch of edits, run a targeted search for HTML table tags in the file to verify there are no remaining tags in the converted region.
9. When all conversions are complete, perform a final verification search:

   ```text
   <table>|</table>|<tr>|</tr>|<td>|</td>
   ```

   The target file must return zero matches.

## Common Table Patterns

### Three-column table with a description

Source:

```html
<table>
<tr><td colspan="3">Description</td></tr>
<tr><td colspan="3">Component description.</td></tr>
<tr><td>Variable</td><td>Type</td><td>Description</td></tr>
<tr><td>Enabled</td><td>boolean</td><td>Whether it is enabled.</td></tr>
</table>
```

Converted to:

```markdown
Description: Component description.

| Variable | Type | Description |
| --- | --- | --- |
| Enabled | boolean | Whether it is enabled. |
```

### Simple summary table without a description

```html
<table>
<tr><td>Component</td><td>Description</td></tr>
<tr><td>Controller</td><td>An embedded logic controller</td></tr>
</table>
```

Converted to:

```markdown
| Component | Description |
| --- | --- |
| Controller | An embedded logic controller |
```

### Table containing a colspan grouping row

```html
<table>
<tr><td>Variable</td><td>Unit</td><td>Value</td></tr>
<tr><td>Available</td><td>boolean</td><td>true</td></tr>
<tr><td colspan="3">Proprietary data from the vehicle:</td></tr>
<tr><td>VehicleId</td><td>string</td><td>...</td></tr>
</table>
```

Converted to:

```markdown
| Variable | Unit | Value |
| --- | --- | --- |
| Available | boolean | true |


**Proprietary data from the vehicle:**

| Variable | Unit | Value |
| --- | --- | --- |
| VehicleId | string | ... |
```

## Validation Checklist

- The target file path is correct and only the user-specified file was modified.
- All target HTML tables have been converted to Markdown pipe tables.
- Each Markdown table has a header and a separator row, unless the original table had no header and the user requested otherwise.
- Leading description rows (the two-row pattern) have been removed from the table and preserved as a preceding `Description: ...` paragraph.
- Colspan grouping rows have been removed from the table and preserved as bold plain text before the subsequent table.
- There are two blank lines between a colspan grouping and the preceding table, and one blank line between the grouping and the following table.
- Non-colspan merged-cell text remains present and each row has a readable, stable column count.
- Original wording, order, punctuation, and any unusual text are not corrected or rewritten.
- A final search for `<table>|</table>|<tr>|</tr>|<td>|</td>` returns zero matches.
- When a narrow-range check is available, prefer it; do not substitute `git diff` for an executable final verification.
