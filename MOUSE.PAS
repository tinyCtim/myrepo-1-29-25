
{$I mouse.his}

{$C+,B-}

{ ^C abortable. No carriage return needed when reading from keyboard. }

PROGRAM MouseInterpreter;

{$I mouse.def}     { constant, type and var }

{Display an environment; used for reporting errors and tracing.}

PROCEDURE display(charpos:progindex);
   VAR posx:integer;
   BEGIN
      FOR posx:=charpos-halfwidth TO charpos+halfwidth DO
         IF (posx>=1) AND
            (posx<=proglen) AND
            (prog[posx]>=' ') {ASCII graphic character}
           THEN write (prog[posx])
           ELSE write(' ');
         writeln;
         writeln(' ':halfwidth,'^')
      END; {display}

 {Report an error and set 'disaster' flag to stop the interpreter.}

PROCEDURE error (code:byte);
   VAR wsp:byte;
   BEGIN
      writeln;
      FOR wsp:=1 TO esp DO
         display(envstack[wsp].charpos);
      display(charpos);
      write('Stack:');
      FOR wsp:=1 TO sp DO
         write(' ',stack[wsp]:1);
      writeln;
      write('***** Error: ');
      CASE code OF
         1:write('Ran off end of program');
         2:write('Calculation stack overflowed');
         3:write('Calculation stack underflowed');
         4:write('Attempted to divide by zero');
         5:write('Attempted to find modulus by zero');
         6:write('Undefined macro');
         7:write('Illegal character follows "#" ');
         8:write('Environment stack overflowed');
         9:write('Environment stack underflowed');
         10:write('Data space exhausted');
         11:write('Illegal character');
         ELSE write(code)
      END; {CASE}
      writeln;
      disaster:=true

   END; {error}

 {Get next character from program buffer and check for end of program.}

PROCEDURE getchar;
   BEGIN
      IF charpos < proglen
         THEN
            BEGIN
               charpos:=charpos+1;
               ch:=prog[charpos]
            END
         ELSE error(1)
      END; {getchar}

 {Backspace the character pointer.}

PROCEDURE backspace;
   BEGIN
      charpos:=charpos-1
   END; {backspace}

 {Push an item onto the calculation stack and check for stack overflow.}

PROCEDURE push (datum:integer);
   BEGIN
      IF sp<stacksize
         THEN
            BEGIN
               sp:=sp+1;
               stack[sp]:=datum
            END
         ELSE error(2)
      END; {push}

 {Pop an item from the calculation stack; check for underflow.}

 FUNCTION pop:integer;
    BEGIN
       IF sp>0
          THEN
             BEGIN
                pop:=stack[sp];
                sp:=sp-1
             END
          ELSE error(3)
       END; {pop}

 {Skip over string; " has been scanned on entry.}

PROCEDURE skipstring;
   BEGIN
      REPEAT
         getchar
      UNTIL ch='"'
   END; {skipstring}

 {Skip bracketed sequences; lch has been scanned on entry.}

PROCEDURE skip(lch,rch:char);
   LABEL 1,2;
   VAR count:byte;
   BEGIN
   count:=1;
   REPEAT
1:    getchar;
2:    IF ch='"'
         THEN skipstring
      ELSE IF ch=''''
         THEN
            BEGIN
               getchar;
               IF ch=lch
                  THEN GOTO 1
               ELSE
                  GOTO 2
            END 
      ELSE IF ch=lch
         THEN count:=count+1
      ELSE IF ch=rch
         THEN count:=count-1
      UNTIL count=0
   END; {skip}

 {Return the binary value of an ASCII digit.}

FUNCTION value(digit:char):byte;
   BEGIN
      value:=ord(digit)-ord('0')
  END; {value}

 {Push an environment;check for environment stack overflow.}

PROCEDURE pushenv(tag:tagtype);
   BEGIN
      IF esp<envstacksize
         THEN
            BEGIN
               esp:=esp+1;
               envstack[esp].tag:=tag;
               envstack[esp].charpos:=charpos;
               envstack[esp].offset:=offset
            END
         ELSE error(8)
      END; {pushenv}

 {Pop an environment;check for environment stack underflow.}

PROCEDURE popenv;
   BEGIN
      IF esp>0
         THEN
            BEGIN
               charpos:=envstack[esp].charpos;
               offset:=envstack[esp].offset;
               esp:=esp-1
            END
         ELSE error(9)
      END; {popenv}

 {The Loader.}

PROCEDURE load;
   VAR filename:string[14];
       i:integer;
   BEGIN
      FOR charpos:=1 TO maxproglen DO
         prog[charpos]:=' ';
      IF NOT newsource
         THEN BEGIN
            write('Enter Mouse program''s name : ');
            readln(filename);
            filenamew:='';
            FOR i:=1 TO length(filename) DO
            filenamew:=filenamew+UpCase(Copy(filename,i,1));
         END; 
      assign(progfile,filenamew);
      reset(progfile);
      charpos:=0;
      disaster:=false;
      WHILE NOT (eof(progfile) OR disaster) DO
         BEGIN
            read(progfile,ch);
            IF ch='~'
               THEN readln(progfile)
            ELSE IF charpos<maxproglen
               THEN
                  BEGIN
                     charpos:=charpos+1;
                     prog[charpos]:=ch
                  END
               ELSE
                  BEGIN
                     writeln('Program is too long');
                     disaster:=true
                  END
               END; {WHILE}
            proglen:=charpos
   END; {load}

 {Construct macro definition table}

PROCEDURE makedeftable;
   BEGIN
      FOR ch:='A' TO 'Z' DO
         macdefs[ch]:=0;
      charpos:=0;
      pch:=' ';
      REPEAT
         getchar;
         IF ch='$'
            THEN
               IF pch<>''''
                  THEN
                     BEGIN
                        getchar; ch:=upcase(ch);
                        IF ch IN ['A'..'Z']
                           THEN macdefs[ch]:=charpos
                     END; 
               pch:=ch
            UNTIL charpos=proglen
         END; {load}

{$I mouse.int}

 {Main program}

   BEGIN
      writeln('MOUSE, Peter Grogono, 1983; Lee Bradley, 2007');
      newsource:=false;	
      load;
      newsource:=true;
      IF NOT disaster
         THEN
            BEGIN
               WHILE (newsource) DO
                  BEGIN
                     newsource:=false;
                     makedeftable;
                     interpret
                  END;
            END;
   END. {MouseInterpreter}

