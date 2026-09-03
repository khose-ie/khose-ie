# C/C++ Coding Rules


The rules within this document do not apply to third-party code or open-source code that is directly incorporated.
The incorporated third-party or open-source code should be kept as unchanged as possible to facilitate subsequent version upgrades and maintenance.


This project uses clang-format to format all header and source files that are not third-party or open-source code.
The code should be formatted according to the rules defined in the clang-format file located at the root of the project.


All rules in this document are divided into the following three levels:

* **[Mandatory]** Must follow this rule.
* **[Required]** Require to follow this rule. If it is necessary to violate this rule due to special circumstances, a explanation must be provided in the code review meeting and get the permission.
* **[Recommended]** Recommend to follow this rule, but it is not mandatory, and explanation is not necessary for your violation.



## Files



* **[Mandatory]** Files and folders should be named using all lowercase letters with `-` for separation.
* **[Mandatory]** File names must adhere to the formatting rule: `modulename-submodulename.cpp`.


```bash
module-a/module-a-submodule.h
module-a/module-a-submodule.cpp
```


* **[Mandatory]** The header of the file should contain comments in doxygen format to document the basic information of the file.

```c
/**
 * @file <FILE_NAME>
 * @author <AUTHOR> <<AUTHOR_EMAIL>>
 * @date <DATE>
 * @brief <BRIEF_DESCRIPTION>
 * @details <DETAILED_DESCRIPTION>
 * @note <NOTE>
 */
```



* **[Mandatory]** Header files should define a macro switch to prevent multiple inclusions. The rule for defining the macro switch is: `_MODULE_PATH_TO_THIS_FILE_H_`. After the macro definition's closing sequence, a comment `//` should be used to indicate the end of the macro definition.


module-a/module-a-submodule.h

```c
#ifndef _MODULE_A_MODULE_A_SUBMODULE_H_
#define _MODULE_A_MODULE_A_SUBMODULE_H_

// code

#endif // _MODULE_A_MODULE_A_SUBMODULE_H_
```



## Formatting


* **[Mandatory]** Indentation must use spaces only (no Tab characters). The indentation width is fixed at **4 spaces** for all C/C++ source and header files. Makefile files are exempt from this rule.



* **[Required]** The maximum level of indentation should be 4 levels deep. When exceeding 4 levels, consider optimizing your code. For state machine implementations using `switch-case` at a single level, the `switch` statement itself is not counted as an indentation level for this limit.



* **[Mandatory]** The maximum line length is 120 characters. It is better to keep statements within one line. For some long statements, should be split into multiple lines, following the default rules of clang-format for splitting.



* **[Recommended]** Do not be sparing with blank lines. When two sections of code are not strongly related logically, it is recommended to insert a blank line between them.



## Comments



* **[Mandatory]** This project uses doxygen-style comments. It is mandatory to create comments for every file, function, class or structure, enumeration, and macros or macro functions.



## Macro



* **[Mandatory]** When using macros to define constants, the names must be in uppercase using the snake case naming convention (underscores between words), and the actual values of the macro definitions must be enclosed in parentheses.

```c
#define THIS_IS_MARCO_VALUE (100) // Good case
```



* **[Mandatory]** The names of macro functions should use lowercase letters with underscores for separation (Snake Case), and starting with a lowercase letter.

```c
#define this_is_a_marco_function(x) (x) // Good case
```



* **[Mandatory]** Macro functions should be enclosed in parentheses or curly braces as appropriate.



```c
#define this_is_a_marco_function(x) ((x) * 2) // Good case

// Good case
#define this_is_another_marco_function(x, y) \
{                                            \
    (x) = (x) + (y);                         \
}
```



* **[Mandatory]** Literal constants other than `0` should not appear in function contexts; corresponding macros should be defined instead. For certain complex formula calculations, they should be defined as macro functions.

```c
unsigned int value = 320; // Bad case

// Good case
#define THE_TARGET_VALUE (320)
unsigned int value = THE_TARGET_VALUE;

value = param * 23 / (16 + 128); // Bad case

// Good case
#define compute_the_result(x) ((x) * 23 / (16 + 128))
value = compute_the_result(param);
```



> For a series of integer constants that have representative significance, they should be defined as enumerations or enumeration classes.



* **[Mandatory]** Do not define macro functions that have context-dependent behavior.

```c
// Bad case
#define marco_function(x) \
{
    x->temp++;
    x->alive += systick;
}
```



## Variables and Types / 变量和类型



* **[Mandatory]** Global and local variable names should use lowercase letters with underscores for separation (Snake Case), and starting with a lowercase letter.

```c
// Good case
unsigned int the_value_name;

// Good case
unsigned int _this_value_name; // start with underline

// Bad case
unsigned int TheValueName; // Camel Case
```



* **[Mandatory]** In any case, should not define non-static global variables, and global variables should not be exposed for direct external use.

```c
// Bad case
unsigned int global_flag;

// Bad case
extern unsigned int global_flag;
```



* **[Mandatory]** All variables must be initialized. For C-style arrays, each element of the array should be initialized.

```c
// Bad case
unsigned int value;
unsigned char* pointer;

// Good case
unsigned int value = 0;
unsigned char* pointer = 0;

// Bad case
unsigned int array[10];
unsigned int array[10] = { 0 };

// Good case
unsigned int array[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
memset(array, 0, sizeof(array));
```



* **[Mandatory]** The names of structures, unions, and C-style enumerations should use strict Camel Case. For C, start with a lowercase module name, continue with upper case Struct name, and end with `_t`. For C++, don't start with a lowercase module name, start with upper case Class name.

```c
// Good case in C
struct osTask_t
{
};

// Good case in C
enum osTaskStatus_t
{
};

// Good case in C++
class os::Task
{
};

// Good case in C++
enum os::TaskStatus
{
};
```



* **[Mandatory]** The names of member fields in classes, structures, and unions should use lowercase letters with underscores for separation (Snake Case).

```c
// Good case
struct moduleStruct_t
{
	unsigned int key_value;
};
```



* **[Mandatory]** The member fields of C-style enumerations should start with lower case module name and continues with upper case type name and use all upper case and underscores for separation (Snake Case).

```c
// Good case
enum someKind_t
{
    SOME_KIND_REMOTE_ONE,
    SOME_KIND_LOCALIZATION_ONE
};

// Good case in C++
enum class SomeKind
{
};

```



* **[Mandatory]** The member fields of C-style enumerations must start with the uppercase version of the enumeration type name. For C++, the member fields of enumeration classes should start with an uppercase letter and use Camel Case.

```c
// Good case
enum someKind_t
{
    SOME_KIND_REMOTE_ONE,
    SOME_KIND_LOCALIZATION_ONE
};

// Bad case
enum someKind_t
{
    REMOTE_ONE,
    LOCALIZATION_ONE
};

//Good case in C++
enum class SomeKind
{
    RemoteOne,
    LocalizationOne
};
```


* **[Mandatory]** For any names (type names, variable names, and parameter names), except for widely used or conventional English abbreviations, and cases where the term itself is an abbreviation, the use of any English abbreviations is prohibited.

```c
// Good case
unsigned int the_last_status;

// Bad case
unsigned int tls; // the last state, but can not be understood

// Good case
unsigned int the_req; // the request, common abbreviation
```



## Statements



* **[Mandatory]** For arithmetic operators such as `+`, `-`, `*`, `/`, `%`, `=` etc., spaces must be used to separate them from variables before and after.

```c
// Good case.
sum = value1 + value2 * value3;

//Wrong case.
sum=value1+value2*value3;
```



* **[Mandatory]** For logical operators such as `&`, `|`, `&&`, `||`, etc., spaces must be used to separate them from variables before and after.

```c
// Good case.
if (check1() && check2())
{
    sum = value1 & value2;
}

//Wrong case.
if (check1()&&check2())
{
    sum=value1|value2;
}
```



* **[Mandatory]** When a conditional expression contains multiple condition expressions, these sub-expressions must be enclosed in parentheses, even if the sub-expressions are individual variables or function calls.

```c
// Good case
if ((value1 == 0) && (value2 > 3) && (function()))
{
	sum = value1 + value2;
}

// Bad case
if (value1 == 0 && value2 > 3 && function())
{
	sum = value1 + value2;
}
```



## Conditional Logic / 条件逻辑



* **[Mandatory]** For conditional statements such as `if`, `for`, `while`, `switch`, etc., add blank lines before and after the code block.

    **【强制】** 针对条件语句`if`，`for`，`while`，`switch`等，代码的前后要添加空行。



```c
// Good case
sum = value + 1;

while (sum < 10)
{
    sum += 1;
}

// Bad case
sum = value + 1;
while (sum < 10)
{
    sum += 1;
}
```



* **[Mandatory]** For conditional statements like `if`, `for`, `while`, `switch`, etc., a space must be added between the keyword and the following parenthesis.

```c
// Good case
if (value == 1) {}

// Bad case
if(value == 1) {}
```



* **[Mandatory]** For conditional statements such as `if`, `for`, `while`, `switch`, etc., curly braces must be used to enclose the code block, regardless of the number of lines of executable statements.

```c
// Bad case
if (value == 0)
	return;

// Good case
if (value == 0)
{
    return;
}
```



* **[Required]** The nesting level of conditional branches should not exceed three levels. When the level is exceeded, attempts should be made to combine or optimize the logic.

```c
// Bad case
if (value1 == 0)
{
    if (value2 == 0)
    {
        if (value3 == 0)
        {
            if (value4 == 0)
            {
                // some code
            } 
        }
    }
}
```



* **[Recommended]** For a single condition or a terminating condition, it should not be written in the form of `if-else` , but rather in the form of astandalone `if` statement or an `if-return` statement.

```c
// Bad case
if (value != 0)
{
}
else
{
    value += 1;
}

// Good case
if (value == 0)
{
    value += 1;
}

// Good case
if (value != 0)
{
    return;
}

value += 1;
```



> It is a misconception that every `if` statement must be followed by an `else` clause.



* **[Required]** The nesting level of loops should not exceed three levels. When the level is exceeded, first attempt to optimize your code.

```c
// Bad case
while (value1 == 0)
{
    while (value2 == 0)
    {
        while (value3 == 0)
        {
            while (value4 == 0) {} 
        }
    }
}
```



* **[Mandatory]** The use of `goto` statements in code is prohibited. If necessary, a `do-while` loop can be used as an alternative.

```c
// Good case
do
{
    if (sum == 0)
    {
        break;
    }
} while (0);

return;

// Bad case
if (sum == 0)
{
    goto exit;
}

exit:
    return;
```



* **[Mandatory]** In `switch` statements, the `case` statements should be indented, but the content of the `case` statements and the final `break` statements must be indented too.

```c
// Good case
switch (code)
{
    case CONDITION1:
	    sum += value;
        break;

    case CONDITION2:
	    sum += value;
        break;
}

// Bad case
switch (code)
{
case CONDITION1:
	sum += value;
    break;

case CONDITION2:
	sum += value;
    break;
}
```



* **[Mandatory]** The content of each `case` statement within a `switch` block must be enclosed in curly braces when it declares any variables, or when required by static analysis tools (e.g., MISRA). For simple single-statement cases without variable declarations, curly braces are recommended but not mandatory.

```c
// Good case (variable declaration requires braces)
switch (code)
{
    case CONDITION1:
    {
        int local_var = 0;
        sum += local_var;
        break;
    }
}

// Good case (single statement, braces optional but acceptable)
switch (code)
{
    case CONDITION1:
        sum += value;
        break;
}
```



* **[Required]** When all possible cases of a `switch` statement can be exhaustively listed, do not add a `default` branch. When it is not possible to exhaustively list all cases of a `switch` statement, a `default` branch must be included.


> The purpose of this is that when certain case values are omitted, the compiler will issue a warning, allowing you to discover which cases you have missed. If a `default` branch is included, it will not issue any warning.



## Functions / 函数



* **[Mandatory]** Function names should use all lowercase letters with underscores for separation (Snake Case), and starting with a lowercase letter.


```c
// Good case
void the_function_name(void);
```


* **[Mandatory]** In the C language, public functions must start with the lowercase module name followed by an underscore. For static functions in C++ and C, they should not start with the module name.


```c
// Good case
void module_name_do_some_action(void);

// Good case
class ModuleName
{
public:
    void do_some_action(void);
}
```



> For the situation where a submodule and its parent module are in the same file in the C language, all functions of the submodule should be static, not starting with the lowercase submodule name and directly write the action as function name.



* **[Mandatory]** The names of function parameters, both formal and actual, should use all lowercase letters with underscores for separation (Snake Case).

```c
// Good case
void module_name_do_some_action(int param1, char* param2);
```



* **[Required]** A function should not have more than five parameters.

```c
// Bad case
void module_name_do_some_action(int param1, int param2, int param3,
                                int param4, int param5, int param6);
```



* **[Mandatory]** When declaring a function, in addition to the type, the formal parameters should also be named so that callers can understand their meanings.

```c
// Good case
void module_name_do_some_action(int time, char* serial_id);

// Bad case
void module_name_do_some_action(int, char*);
```



* **[Mandatory]** When declaring or invoking a function, the function name should be immediately followed by the opening parenthesis (with no space), and the parentheses enclosing the argument list should also be immediately adjacent to the first and last arguments (with no spaces).

```c
// Good case
void module_name_do_some_action(int time, char* serial_id);

// Bad case
void module_name_do_some_action ( int time, char* serial_id );
```



* **[Mandatory]** When declaring or invoking a function, there should be a space between the comma , and the preceding parameter, and the comma , and the following parameter should be adjacent (with no space).

```c
// Good case
void module_name_do_some_action(int time, char* serial_id);

// Bad case
void module_name_do_some_action(int time,char* serial_id);
```



* **[Mandatory]** When declaring a function, the return type and the function name should not be written on separate lines.

```c
// Good case
void module_name_do_some_action(int time, char* serial_id);

// Bad case
void 
module_name_do_some_action(int time,char* serial_id);
```



* **[Required]** Recursive calls within a function should not be used.

> When recursion is necessary under certain circumstances, the termination condition of the recursive call must be explicitly stated in the comments and thoroughly explained during the code review meeting.



* **[Recommended]** The length of a function should ideally be controlled within 100 lines. Functions that handle hardware initialization (e.g., clock tree configuration, peripheral multiplexing setup) may reasonably exceed this limit, but the justification must be provided during code review.



* **[Required]** Doxygen-style comments at the top of each function are mandatory, covering the function's purpose, parameters, and return values. When a function has more than one parameter, each parameter should have its own `@param` block.



* **[Required]** Comments within the function body should be used sparingly and only to explain **why** a particular piece of code exists (e.g., "divide by 3.14159 to convert radians to degrees"), not to describe **what** the code does (the code itself should be self-explanatory). When a function's internal logic is complex enough to require extensive inline comments, consider refactoring it into smaller, better-named helper functions.

```c
/**
 * @brief The function action.
 * @details The detail description of this function is wrote here.
 * @param buf The buffer array.
 * @param size The buffer size.
 * @return The return value meaning.
 * @retval 0 The reason and condition when function return 0.
 * @retval 1 The reason and condition when function return 1.
 */
int example_function(char* buf, unsigned int size) {}
```



* **[Required]** If the use of global variables is necessary, they should only be used in the top-level functions of a module. Sub-functions should not use global variables directly; instead, pointers or references to the global variables should be passed into the sub-functions.

```c
static int global_value;

// Bad case
void sub_function(void)
{
    global_value += 2;
}

void top_interface(void)
{
    global_value += 1;
    sub_function();
}

// Good case;
void sub_function(int* value)
{
    *value += 2;
}

void top_interface(void)
{
    global_value += 1;
    sub_function(&global_value);
}
```


