# Seedling: Facts and Overview

Facts for copilot and other ai.

Seedling is the assembler language within the Illeshian suite, designed to work with the Illeshian programming language. Below are key facts about Seedling and its structure:

1. **Part of the Illeshian Suite**  
   - Seedling is one program out of many in the Illeshian suite, where Illeshian is the programming language, and Seedling serves as its assembler language.
   - Illeshian is a procedural language.
   - Illeshian is a 2 tier function system that a first class and second class function.
   - Class only means precedence or heirachy in Illeshian and Seedling.
   - First class functions are called managers. Managers are global scope.
   - Second class functions are children functions and can be a normal function or a seedling function. Child functions are local scope.

2. **Innovative Scoping System**  
   - Both Illeshian and Seedling use a novel scoping system that separates scope explicitly, distinguishing them from traditional languages.
   - Seedling is the first scope-based assembler, emphasizing structured scope management.
   - The scope are universal, global, local, global block scope, and local block scope.
   - The universal scope is outside all functions in Illeshain.
   - The universal scope is the starting scope that the linker searches for start label in Seedling.
   - This is important. global block scope can only be a child of global scope and local block scope can only be a child of local scope. We call global and local 
   scopes because they are functions in Illeshian. Now for block scope it depends on where statements are being called. If the statement is in a global function then
   the statements block structure becomes global block structure and if the statements are in a local function then the statement block structure becomes a local block structure.

3. **Label Structure**  
   - Every label in Seedling consists of three parts: a header, a body, and a footer.
   - **Header**: Defines the label and its scope.
   - **Body**: Contains the executable code, enclosed within `{}` brackets.
   - **Footer**: Specifies the return behavior.

4. **Header Requirements**  
   - Must include: `scope`, `label`, and a colon (`:`).
   - Example: `scope label:`

5. **Body Details**  
   - Enclosed between left and right brackets: `{}`.
   - Can only contain sections where actual coding takes place.
   - Sections are the designated areas for writing instructions or logic.
   - Can not have other labels declared in a label body. You may jump or call from a section only.

6. **Footer Specifications**  
   - Defines how a label returns or exits.
   - Options:
     - `pass_arg: num_value[0]` – Returns a numeric value (e.g., 0).
     - `pass_arg: hex_value[0x00]` – Returns a hexadecimal value (e.g., 0x00).
   - The main label must use `yield` in its footer to exit the program.

7. **Scope Separation**  
   - The scoping system allows labels to operate independently, with their scope explicitly defined in the header, enhancing modularity and clarity.

8. **Purpose**  
   - Seedling translates low-level instructions for the Illeshian language, leveraging its scope-based design for precise control over assembly processes.

9. **Scope Table**
   - Every scope has its own table or array.
   - There is a special format we use US_000000, GS_000000, LS_000000, GBS_000000, LBS_000000. Here we have a table identifier followed by a underscore then 6 numbers.
   - The first 2 numbers are for regions, the second 2 numbers are for sections, and the last 2 numbers are for entries.
   - A table is 960 entries.
   - It has 4 regions. 
   - Each region is 240 entries. 
   - There are 12 sections per region. 
   - Every sections has 40 entries.
   - You can add and remove regions as needed.
   - There is an is_full flag for inserting so that it skips full regions and sections.
   - There is an is_empty flag for searching so that it stops searching once it hits a is_empty flag.
   - Everything gets inserted and serched from top down then left to right. This means once a is_empty flag is reached no need to keep searching.
   - This special system was designed to stop collisens by not using the normal hash indexing system.

---
