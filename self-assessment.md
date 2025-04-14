# Self Assessment

## Part A - Individual Assessment

I was a one-man team; all work done to the project was done by me. I felt like this project was really interesting and challenging; but I learned a lot about compiler development throught this project. This project required me to move swiftly and really stop and think about what the implmentation of each component would look like. However, I found the abundance of online resources really helpful in completing the compiler's components efficently and on time.

The compiler involved building out three main components: the lexer, parser (and it's subcomponent, the resolver), and the code generator. Each of these came with their own challenges. For example, the parser was challenging in the error handling/reporting aspect; it was hard to account for each edge case that would generate an error. The generator was difficult in that it required working with some more advanced areas of assembly (which I had to refresh myself on). I didn't have too much trouble with the lexer and found it fairly intuitive. At the end of the project, we have a working C compiler that can generate x86 assembly code for a subset of the C programming language.

## Part B - Group Assessment

Note: I didn't have a group (other than myself), so I will be discussing how this project could be divided into an even amount of work among a group and what it would kind of look like.

As mentioned in the previous paragraphs. The overall system (the compiler) is built up of smaller sub-components. Each of these components has it's own role: the lexer - to generate a list of tokens based on the input code, the parser - to build an abstract syntax tree for the input code, the resolver - to enrich and simplify the AST before code generation, and the code generator - to generate the actual output code. I think this makes the project very intuitive in the way that it would break up among group members. In a group of four, you could have each group member build out a component of their choosing.

I think having a solid design before going into the implementation would make this project easier among group members. Each component plays into the next, so you would need to at least be familiar with the input that the next component accepts. Communication would be needed by each group member to ensure that each sub-component be compatible with the next in the compilation process. I belive that this communication step would be where most people have issues. The initial break up of the project is simple, so there will be some leeway there, but ensuring that each component plays into all of the rest is key.