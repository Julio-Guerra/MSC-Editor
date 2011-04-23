grammar z120;

options
{
  language = C;
  k = 2; // 3 ?
}

@parser::includes
{
  # include "msc/all.hh"
}

fragment
Letter:
  'a'..'z'
  | 'A'..'Z'
;

fragment
Decimal_Digit:
   '0'..'9'
;

fragment
National:
  '`' | '\\' | '{' | '|' | '}' | '~' | '^'
;

Character_String:
  '\''
  (
    Letter
    | Decimal_Digit
    | Other_Character
    | Special
    | '.'
    | '_'
    | ' '
    | '\'\''
  )*
  '\''
;

fragment
Other_Character:
   '?' | '%' | '+' | '-' | '!' | '/' | '*' | '"' | '='
;

fragment
Special:
  '@' | '&' | '(' | ')' | '[' | ']' | '<' | '>' | '#' | ',' | ';' | ':'
;

Qualifier:
  '<<'
  (
    Letter
    | Decimal_Digit
    | Other_Character
    | Special
    | '.'
    | '_'
    | ' '
    | '\''
  )*
  '>>'
;

Name:
  (Letter | Decimal_Digit | National | '_' | '.')+
;

string:
  pure_data_string
;

pure_data_string:
  non_parenthesis
;

parenthesis:
  nestable_par | equal_par | non_nestable_par
;

nestable_par:
  '(' pure_data_string ')'
  '<' pure_data_string '>'
  '{' pure_data_string '}'
;

non_parenthesis:
  non_par_non_escape | escapechar (escapechar | Character_String)
;

non_par_non_escape:
  Character_String | Name
;

non_nestable_par:
   '(' (Letter | Decimal_Digit | Other_Character | Special | '.' | '_' | '\'')* ')'
   '<' (Letter | Decimal_Digit | Other_Character | Special | '.' | '_' | '\'')* '>'
   '{' (Letter | Decimal_Digit | Other_Character | Special | '.' | '_' | '\'')* '}'
;

WHITESPACE:
   ('\t' | ' ' | '\r' | '\n')+ { $channel = HIDDEN; }
;


// ----- Comment
end:
   (comment)? ';'
;

comment:
   'comment' Character_String
   {add_element_comment(context, (char*) $Character_String.text->chars);}
;

text_definition:
   'text' Character_String end
   {add_global_comment(context, (char*) $Character_String.text->chars);}
;

NOTE:
   '/' '*' (options {greedy=false;} : .)* '*' '/' { $channel = HIDDEN; }
;

NOTE_II:
   '/' '/' (options {greedy=false;} : .)* '\n' { $channel = HIDDEN; }
;

// ----- Message Sequence Chart Document

// non-standard: Z.120 doesn't define top-level nonterminal
textual_msc_file [struct s_Z120* my_z120] returns [struct s_Msc** my_msc]:
   {
     context = new_context();
     printer = my_z120;

     if(my_z120 != NULL)
       add_z_fun(context, $my_z120);
   }
   (document_head)? (message_sequence_chart)*
   {
     check_references_fun(context);
     $my_msc = get_total_msc_fun(context);
     delete_context(context);
   }
;

textual_msc_document:
   document_head
   textual_defining_part textual_utility_part
;

document_head:
   'mscdocument' instance_kind ('related' 'to' sdl_reference)?
   (inheritance)? end
   ((parenthesis_declaration)?
   data_definition
   using_clause
   containing_clause
   message_decl_clause
   timer_decl_clause)?
;

textual_defining_part:
   (defining_msc_reference)*
;

textual_utility_part:
   'utilities' (containing_clause)? (defining_msc_reference)*
;

defining_msc_reference:
   'reference' (virtuality)? Name
;

virtuality:
   'virtual' | 'redefined' | 'finalized'
;

using_clause:
   ('using' instance_kind end)*
;

containing_clause:
   ('inst' instance_item)+
;

instance_item:
   Name (':' instance_kind)? (inheritance)?
   (decomposition)?
   (dynamic_decl_list | end)
;

inheritance:
   'inherits' instance_kind
;

message_decl_clause:
   ('msg' message_decl end)*
;

timer_decl_clause:
   ('timer' timer_decl end)*
;

sdl_reference:
   identifier
;

identifier:
   (Qualifier)? Name
;


// ----- Basic MSC


//add nonstrict endmsc "(endmac end)?" for better error message handling
message_sequence_chart:
   {
      init(context);
   }
   (virtuality)? 'msc' msc_head ( ('expr' | (hmsc_statement_without_initial)* initial_node)=> hmsc | msc )
   ('endmsc' end { set_end_msc_fun(context);})?
   {
      check_collections_fun(context);
      msc_was_read_fun(context);
   }
;

msc:
   {
      new_bmsc_fun(context);
   }
   msc_body
;

msc_head:
   Name
   {
      set_msc_name_fun(context, (char*) $Name.text->chars);
   }
   (msc_parameter_decl)? (time_offset)? end
   (msc_inst_interface)? msc_gate_interfacez
;

msc_parameter_decl:
   '(' msc_parm_decl_list ')'
;

msc_parm_decl_list:
   msc_parm_decl_block_first (end msc_parm_decl_block)*
;

/*
 * add call methods for syntax regulation
 * each rewrite rule can be occured only once
 */
msc_parm_decl_block:
   data_parameter_decl {set_data_parameter_decl(context);}
 | instance_parameter_decl {set_instance_parameter_decl(context);}
 | message_parameter_decl {set_message_parameter_decl(context);}
 | timer_parameter_decl {set_timer_parameter_decl(context);}
;

msc_parm_decl_block_first:
   data_parameter_decl_first
 | instance_parameter_decl
 | message_parameter_decl
 | timer_parameter_decl
;

instance_parameter_decl:
   'inst' instance_parm_decl_list
;

instance_parm_decl_list:
   instance_parameter_name (':' instance_kind)? (',' instance_parm_decl_list)?
;

instance_parameter_name:
   Name
;

message_parameter_decl:
   'msg' message_parm_decl_list
;

message_parm_decl_list:
   message_decl_list
;

timer_parameter_decl:
   'timer' timer_parm_decl_list
;

timer_parm_decl_list:
   timer_decl_list
;

msc_inst_interface:
   containing_clause
;

instance_kind:
   (kind_denominator)? identifier
;

kind_denominator:
   Name
;

msc_gate_interface:
   (msc_gate_def)*
;

msc_gate_def:
   'gate' (msg_gate | method_call_gate | reply_gate |
   create_gate | order_gate) end
;

msg_gate:
   def_in_gate | def_out_gate
;

method_call_gate:
   def_out_call_gate | def_in_call_gate
;

reply_gate:
   def_out_reply_gate | def_in_reply_gate
;

create_gate:
   def_create_in_gate | def_create_out_gate
;

order_gate:
   def_order_in_gate | def_order_out_gate
;

msc_body:
   (msc_statement)*
;

msc_statement:
   text_definition | event_definition
;

event_definition:
   Name
   {
      set_instance_name_fun(context, (char*) ($Name.text->chars));
   }
   ':' instance_event_list
   | instance_name_list ':' multi_instance_event_list
;

instance_event_list:
   (instance_event)+
;

instance_event:
   orderable_event | non_orderable_event
;

orderable_event:
   (
     'label' Name end
     {
        set_event_name_fun(context, (char*) ($Name.text->chars));
     }
   )?
   (
     message_event
     | method_call_event
     | create
     | timer_statement
     | action
   )
   (
     'before' order_dest_list
     {
        add_relation_fun(context, before);
     }
   )?
   (
     'after' order_dest_list
     {
        add_relation_fun(context, after);
     }
   )?
   end
   (
     {
       set_time_event_fun(context);
     }
     'time' time_dest_list end
     {
       set_time_event_false_fun(context);
     }
   )?
   {
      set_not_create_event_fun(context);
   }
;

order_dest_list:
   order_dest (',' order_dest_list)?
;

time_dest_list:
   (time_dest ('origin' { set_origin_fun(context); } )?)?
   time_interval { add_time_relation_ref_fun(context); } (',' time_dest_list)?
;

time_dest:
   {set_time_dest_fun(context);}
   (
   name_a = Name {set_time_reference_event_fun(context, (char*) $name_a.text->chars);}
   |
   ('top' { set_second_time_rel_kind_fun(context, top); }
   | 'bottom' { set_second_time_rel_kind_fun(context, bottom); })
   (reference_identification | name_b = Name { set_time_reference_node_fun(context, (char*) $name_b.text->chars);} )
   )
;

non_orderable_event:
   start_method
   | end_method
   | start_suspension
   | end_suspension
   | start_coregion { start_coregion_fun(context); }
   | end_coregion { end_coregion_fun(context); }
   | shared_condition
   | shared_msc_reference
   | shared_inline_expr
   | instance_head_statement { new_instance_fun(context); }
   | instance_end_statement  { end_instance_fun(context); }
   | stop
;

instance_name_list:
   Name (',' Name)+ | 'all'
;

multi_instance_event_list:
   (multi_instance_event)+
;

multi_instance_event:
   condition | msc_reference | inline_expr
;


// ----- Instance

instance_head_statement:
   'instance' (instance_kind)? (decomposition)? end
;

instance_end_statement:
   'endinstance' end
;


// ----- Message

message_event:
   message_output | message_input
;

message_output:
   'out' msg_identification 'to'
   (input_address
   {
      message_fun(context, (char *)$msg_identification.text->chars, output);
   }
   | 'lost' (input_address)?
   {
      incomplete_message_fun(context, (char *) $msg_identification.text->chars, output);
   }
   )
;

message_input:
   'in' msg_identification 'from'
   (output_address
   {
      message_fun(context, (char *)$msg_identification.text->chars, input);
   }
   | 'found' (output_address)?
   {
      incomplete_message_fun(context, (char *)$msg_identification.text->chars, input);
   }
   )
;

incomplete_message_event:
   incomplete_message_output | incomplete_message_input
;

incomplete_message_output:
   'out' msg_identification 'to' 'lost' (input_address)?
   {
      incomplete_message_fun(context, (char *) $msg_identification.text->chars, output);
   }
;

incomplete_message_input:
   'in' msg_identification 'from' 'found' (output_address)?
   {
      incomplete_message_fun(context, (char *)$msg_identification.text->chars, input);
   }
;

msg_identification:
   (Name (',' Name)? |
    ',' Name
    {
      missing_message_label_fun(context);
    }) ('(' parameter_list ')')?
;

output_address:
   Name | ('env' | reference_identification) ('via' Name)?
;

reference_identification:
   'reference' msc_reference_identification
 | 'inline' inline_expr_identification
;

input_address:
   Name | ('env' | reference_identification) ('via' Name)?
;


// ----- Control Flow

method_call_event:
   call_out | call_in | reply_out | reply_in
;

call_out:
   'call' msg_identification 'to' (input_address | 'lost' (input_address)?)    //merged call_out and incomplete_call_out
;

call_in:
   'receive' msg_identification 'from' (output_address | 'found' (output_address)?) //merged call_in and incomplete_call_in
;

reply_out:
   'replyout' msg_identification 'to' (input_address | 'lost' (input_address)?) //merged reply_out and incomplete_reply_out
;

reply_in:
   'replyin' msg_identification 'from' (output_address | 'found' (output_address)?) //merged reply_in and incomplete_reply_in
;

start_method:
   'method' end
;


end_method:
   'endmethod' end
;

start_suspension:
   'suspension' end
;

end_suspension:
   'endsuspension' end
;


// ----- Environment and Gates

actual_out_gate:
   (Name)? 'out' msg_identification 'to' input_dest
;

actual_in_gate:
   (Name)? 'in' msg_identification 'from' output_dest
;

input_dest:
   'lost' (input_address)? | input_address
;

output_dest:
   'found' (output_address)? | output_address
;

def_in_gate:
   (Name)? 'out' msg_identification 'to' input_dest
;

def_out_gate:
   (Name)? 'in' msg_identification 'from' output_dest
;

actual_order_out_gate:
   Name 'before' order_dest
;

order_dest:
   Name
   {
      add_order_event_fun(context, (char*) $Name.text->chars);
   }
   | ('env' | reference_identification) 'via' Name
;

actual_order_in_gate:
   Name
   ('after' order_dest_list)?
;

def_order_in_gate:
   Name 'before' order_dest
;

def_order_out_gate:
   Name
   ('after' order_dest_list)?
;

actual_create_out_gate:
   'create' 'out' create_gate_identification 'create' create_target
;

actual_create_in_gate:
   'create' 'in' create_gate_identification
;

create_target:
   Name | ('env' | reference_identification) ('via' Name)?
;

def_create_in_gate:
   'create' 'out' (create_gate_identification)? 'create' create_target
;

def_create_out_gate:
   'create' 'in' create_gate_identification
;

inline_out_gate:
   def_out_gate
   ('external' 'out' msg_identification 'to' input_dest)?
;

inline_in_gate:
   def_in_gate
   ('external' 'in' msg_identification 'from' output_dest)?
;

inline_out_call_gate:
   def_out_call_gate
   ('external' 'call' msg_identification 'to' input_dest)?
;

inline_in_call_gate:
   def_in_call_gate
   ('external' 'receive' msg_identification 'from' output_dest)?
;

inline_out_reply_gate:
   def_out_reply_gate
   ('external' 'replyout' msg_identification 'to' input_dest)?
;

inline_in_reply_gate:
   def_in_reply_gate
   ('external' 'replyin' msg_identification 'from' output_dest)?
;

inline_create_out_gate:
   def_create_out_gate
   ('external' create)?
;

inline_create_in_gate:
   def_create_in_gate
   ('external' 'create' 'from' create_source)?
;

create_source:
   Name |
   ('env' | reference_identification) ('via' create_gate_identification)?
;

inline_order_out_gate:
   Name
   (('after' order_dest_list)? 'external' 'before' order_dest)?
;

inline_order_in_gate:
   Name 'before' order_dest
   ('external' ('after' order_dest_list)?)?
;

actual_out_call_gate:
   (Name)? 'call' msg_identification 'to' input_dest
;

actual_in_call_gate:
   (Name)? 'receive' msg_identification 'from' output_dest
;

def_in_call_gate:
   (Name)? 'call' msg_identification 'to' input_dest
;

def_out_call_gate:
   (Name)? 'receive' msg_identification 'from' output_dest
;

actual_out_reply_gate:
   (Name)? 'replyout' msg_identification 'to' input_dest
;

actual_in_reply_gate:
   (Name)? 'replyin' msg_identification 'from' output_dest
;

def_in_reply_gate:
   (Name)? 'replyout' msg_identification 'to' input_dest
;

def_out_reply_gate:
   (Name)? 'replyin' msg_identification 'from' output_dest
;

gate_identification:
   Name
;

create_gate_identification:
   (gate_identification ':')? instance_kind
;


// ----- Condition

shared_condition:
   (shared)? condition_identification shared end
;

condition_identification:
   { clear_condition_name_fun(context); }
   'condition' condition_text
;

condition_text:
   condition_name_list { set_condition_name_fun(context, (char*) $condition_name_list.text->chars); }

   | 'when' { set_condition_name_fun(context, "when "); }
     (condition_name_list { set_condition_name_fun(context, (char*) $condition_name_list.text->chars); }
     | expr = ( '(' expression ')' ) { set_condition_name_fun(context, (char*) $expr.text->chars); }
     )

   | 'otherwise' { set_condition_name_fun(context, "otherwise"); }

// *** proprietary Z.120 extension
   | 'for' { set_condition_name_fun(context, "for "); }
     (a=expression b='%')  { set_condition_name_fun(context, (char*) $a.text->chars); set_condition_name_fun(context, (char*) $b.text->chars); }
;

condition_name_list:
   Name (',' condition_name_list)?
;

shared:
   'shared' ((shared_instance_list)? | 'all')
;

shared_instance_list:
   Name (',' shared_instance_list)?
;

condition:
   (shared)? condition_identification end
;


// ----- Timer

timer_statement:
   starttimer | stoptimer | timeout
;

starttimer:
   'starttimer' Name (',' Name)?
   (duration)?
   ('(' parameter_list ')')?
;

duration:
   '[' (durationlimit)? (',' durationlimit)? ']'
;

durationlimit:
   string | 'inf'
;

stoptimer:
   'stoptimer' Name (',' Name)?
;

timeout:
   'timeout' Name (',' Name)?
   ('(' parameter_list ')')?
;


// ----- Action

action:
   'action' action_statement
;

/* if needed
action_statement:
   ( ('def' |  'undef' | expression RIGHT_BIND_SYMBOL | pattern LEFT_BIND_SYMBOL
   ) => data_statement_list )
   |  informal_action
;*/

action_statement:
   informal_action | data_statement_list
;

informal_action:
   Character_String
;


// ----- Instance creation

create:
   'create' Name ('(' parameter_list ')')?
;


// ----- Instance stop

stop:
   'stop' end
;


// ----- Data concepts

parenthesis_declaration:
   'parenthesis' par_decl_list end
;

par_decl_list:
   (nestable_par_pair | non_nestable_par_pair | equal_par_decl | escape_decl)
   (par_decl_list)?
;

nestable_par_pair:
   'nestable' pair_par_list end
;

non_nestable_par_pair:
   'nonnestable' pair_par_list end
;

equal_par_decl:
   'equalpar' equal_par_list end
;

escape_decl:
   'escape' escapechar
;

pair_par_list:
   pair_par (escape_decl)? (',' pair_par_list)?
;

pair_par:
   ('\'' | Letter | Decimal_Digit | Other_Character | Special | '.' | '_')
   Character_String
   ('\'' | Letter | Decimal_Digit | Other_Character | Special | '.' | '_')
   Character_String
   ('\'' | Letter | Decimal_Digit | Other_Character | Special | '.' | '_')
;

equal_par_list:
   equal_par (escape_decl)? (',' equal_par_list)?
;

equal_par:
   unmatched_string (equal_par)?
;

unmatched_string:
   non_parenthesis (nestable_par)? //(unmatched_string)?
;

escapechar:
  ('\'' | Letter | Decimal_Digit | Other_Character | Special | '.' | '_')
  Character_String
  ('\'' | Letter | Decimal_Digit | Other_Character | Special | '.' | '_')
;



// ----- Declaring data

message_decl_list:
   message_decl ( (end ~('inst' | 'msg' | 'timer' | 'variables'))=> end message_decl_list | )
;

message_decl:
   message_name_list (':' '(' type_ref_list ')')?
;

message_name_list:
   Name (',' message_name_list)?
;

timer_decl_list:
   timer_decl  ( (end ~('inst' | 'msg' | 'timer' | 'variables'))=> end timer_decl_list | )
;

timer_decl:
   timer_name_list  (duration)?
   (':' '(' type_ref_list ')')?
;

timer_name_list:
   Name (',' timer_name_list)?
;

type_ref_list:
   string (',' type_ref_list)?
;

dynamic_decl_list:
   'variables' variable_decl_list end
;

variable_decl_list:
   variable_decl_item ((end string (',' | ':' string))=>end variable_decl_list |)
;

variable_decl_item:
   variable_list ':' string
;

variable_list:
   string (',' variable_list)?
;

data_definition:
   ('language' Name end)?
   (wildcard_decl)?
   ('data' string end)?
;

wildcard_decl:
   'wildcards' variable_decl_list end
;


// ----- Static Data
data_parameter_decl_first:
   ('variables')? variable_decl_list
;

data_parameter_decl:
   'variables' variable_decl_list
;

actual_data_parameters:
   ('variables')? actual_data_parameter_list
;

actual_data_parameter_list:
   string (',' actual_data_parameter_list)?
;


// ----- Bindings

binding:
   (pattern LEFT_BIND_SYMBOL)=> left_binding | right_binding
;

left_binding:
   pattern LEFT_BIND_SYMBOL expression
;

LEFT_BIND_SYMBOL:
   ':='
;

right_binding:
   expression RIGHT_BIND_SYMBOL pattern
;

RIGHT_BIND_SYMBOL:
   '=:'
;

expression:
   string
;

pattern:
   string //| wildcard
;

//wildcard:
//   string
//;


// ----- Data in message and timer paramerers

parameter_list:
   parameter_defn (',' parameter_list)?
;

parameter_defn:
   //binding  |
   expression // | pattern
;


// ----- Data in action boxes

data_statement_list:
   data_statement (',' data_statement_list)?
;

data_statement:
   define_statement | undefine_statement | binding
;

define_statement:
   'def' string
;

undefine_statement:
   'undef' string
;


// ----- Time Offset

time_offset:
   'offset' expression | 'inf'   //inf has been added for accept inf in time definition but it should be in expression to
;


// ----- Time Points

/*
 * Extend the Z120 standart with negative time interval
 */
time_point:
   ('@' { set_absolut_first_or_second_true_fun(context); } )?
   ('-' { add_time_fun(context, "-"); } )?
   (expression { add_time_fun(context, (char*) $expression.text->chars); }
   | 'inf' { add_time_fun(context, "inf"); } ) //inf has been added for accept inf in time definition but it should be in expression to
;


// ----- Measurements

measurement:
   rel_measurement
 | abs_measurement
;

rel_measurement:
   '&' pattern
;

abs_measurement:
   '@' pattern
;


// ----- Time Interval

time_interval:
   { clear_time(context); }
   (interval_label)?
   ( (('@')? ('(' | '[') (time_point)? ',')=>  bounded_time
   (measurement)?
   | singular_time )
;

/*
time_interval:
   (interval_label)? singular_time
 | (interval_label)? bounded_time
   (measurement)?
;
*/

/* Where an interval label is used, the keyword int_boundary must appear in the programming
representation, and must be absent in the graphical representation.
*/

//interval_label:
//   ('int_boundary')? Name
//;

interval_label:
   ('int_boundary') Name
;

singular_time:
   ('[' { add_time_fun(context, "["); }
   time_point { duplicate_time_point(context); }
   ']' { add_time_fun(context, "]"); }
   addition_time? )
 | measurement
;

bounded_time:
   ('@' { set_absolut_time_true_fun(context); })?
   left_bracket { add_time_fun(context, (char*) $left_bracket.text->chars); }
   time_borders
   right_bracket { add_time_fun(context, (char*) $right_bracket.text->chars); }
   (addition_time)?
;

left_bracket:
  ('(' | '[')
;

time_borders:
  (time_point)?
  ',' { add_time_fun(context, ","); }
  (time_point)?
;

right_bracket:
  (')' | ']')
;
/*
 * Extend the Z120 standart with new definition of time interval.
 *
 * It supports definition as a chain of intervals connected with +
 */
addition_time:
  '+' { add_time_fun(context, "+"); }
  ( (('@')? ('(' | '[') (time_point)? ',')=>  bounded_time | singular_time)
;


// ----- Coregion

start_coregion:
   'concurrent' end
;

end_coregion:
   'endconcurrent' end
;


// ----- Inline expression

shared_inline_expr:
   (extra_global)? (shared_loop_expr | shared_opt_expr |
   shared_alt_expr | shared_seq_expr | shared_par_expr | shared_exc_expr)
   ('time' time_interval end)?
   ('top' time_dest_list end)?
   ('bottom' time_dest_list end)?
;

extra_global:
   'external'
;

shared_loop_expr:
   'loop' (loop_boundary)? 'begin' (inline_expr_identification)? shared end
   (inline_gate_interface)? (instance_event_list)?
   'loop' 'end' end
;

shared_opt_expr:
   'opt' 'begin' (inline_expr_identification)? shared end
   (inline_gate_interface)? (instance_event_list)?
   'opt' 'end' end
;

shared_exc_expr:
   'exc' 'begin' (inline_expr_identification)? shared end
   (inline_gate_interface)? (instance_event_list)?
   'exc' 'end' end
;

shared_alt_expr:
   'alt' 'begin' (inline_expr_identification)? shared end
   (inline_gate_interface)? (instance_event_list)?
   ('alt' end (inline_gate_interface)? (instance_event_list)?)*
   'alt' 'end' end
;

shared_seq_expr:
   'seq' 'begin' (inline_expr_identification)? shared end
   (inline_gate_interface)? (instance_event_list)?
   ('seq' end (inline_gate_interface)? (instance_event_list)?)*
   'seq' 'end' end
;

shared_par_expr:
   'par' 'begin' (inline_expr_identification)? shared end
   (inline_gate_interface)? (instance_event_list)?
   ('par' end (inline_gate_interface)? (instance_event_list)?)*
   'par' 'end' (time_interval)? end
;

inline_expr:
   (extra_global)? (loop_expr | opt_expr | alt_expr |
   seq_expr | par_expr | exc_expr)
   ('time' time_interval end)?
   ('top' time_dest_list end)?
   ('bottom' time_dest_list end)?
;

loop_expr:
   'loop' (loop_boundary)? 'begin' (inline_expr_identification)? end
   (inline_gate_interface)? msc_body
   'loop' 'end' end
;

opt_expr:
   'opt' 'begin' (inline_expr_identification)? end
   (inline_gate_interface)? msc_body
   'opt' 'end' end
;

exc_expr:
   'exc' 'begin' (inline_expr_identification)? end
   (inline_gate_interface)? msc_body
   'exc' 'end' end
;

alt_expr:
   'alt' 'begin' (inline_expr_identification)? end
   (inline_gate_interface)? msc_body
   ('alt' end (inline_gate_interface)? msc_body)*
   'alt' 'end' end
;

seq_expr:
   'seq' 'begin' (inline_expr_identification)? end
   (inline_gate_interface)? msc_body
   ('seq' end (inline_gate_interface)? msc_body)*
   'seq' 'end' end
;

par_expr:
   'par' 'begin' (inline_expr_identification)? end
   (inline_gate_interface)? msc_body
   ('par' end (inline_gate_interface)? msc_body)*
   'par' 'end' end
;

loop_boundary:
   '<' inf_natural (',' inf_natural)? '>'
;

inf_natural:
   'inf' | expression
;

inline_expr_identification:
   Name
;

inline_gate_interface:
   ('gate' inline_gate end)+
;

inline_gate:
   inline_out_gate | inline_in_gate |
   inline_create_out_gate | inline_create_in_gate |
   inline_out_call_gate | inline_in_call_gate |
   inline_out_reply_gate | inline_in_reply_gate |
   inline_order_out_gate | inline_order_in_gate
;


// ----- MSC reference

shared_msc_reference:
   'reference' (msc_reference_identification ':')?
   msc_ref_expr shared end
   ('time' time_interval end)?
   ('top' time_dest_list end)?
   ('bottom' time_dest_list end)?
   reference_gate_interface
;

msc_reference:
   'reference' (msc_reference_identification ':')?
   msc_ref_expr end
   ('time' time_interval end)?
   ('top' time_dest_list end)?
   ('bottom' time_dest_list end)?
   reference_gate_interface
;

msc_reference_identification:
   Name
;

msc_ref_expr:
   msc_ref_par_expr ('alt' msc_ref_par_expr)*
;

msc_ref_par_expr:
   msc_ref_seq_expr ('par' msc_ref_seq_expr)*
;

msc_ref_seq_expr:
   msc_ref_ident_expr ('seq' msc_ref_ident_expr)*
;

msc_ref_ident_expr:
   'loop' (loop_boundary)? msc_ref_ident_expr
   | 'exc' msc_ref_ident_expr
   | 'opt' msc_ref_ident_expr
   | 'empty'
   | (parent)* Name
   {
      set_reference_name_fun(context, (char*) ($Name.text->chars));
   }
   (actual_parameters)?
   | '(' msc_ref_expr ')'
;

actual_parameters:
   '(' actual_parameters_list ')'
;

actual_parameters_list:
   actual_parameters_block (end actual_parameters_list)?
;

actual_parameters_block:
   actual_data_parameters
 | actual_instance_parameters
 | actual_message_parameters
 | actual_timer_parameters
;

actual_instance_parameters:
   'inst' actual_instance_parm_list
;

actual_instance_parm_list:
   actual_instance_parameter (',' actual_instance_parm_list)?
;

actual_instance_parameter:
   Name
;

actual_message_parameters:
   'msg' actual_message_list
;

actual_message_list:
   Name (',' actual_message_list)?
;

actual_timer_parameters:
   'timer' actual_timer_list
;

actual_timer_list:
   Name (',' actual_timer_list)?
;

parent:
   '#'
;

reference_gate_interface:
   (end 'gate' ref_gate)*
;

ref_gate:
//   actual_out_gate | actual_in_gate |
   actual_order_out_gate | actual_order_in_gate |
//   actual_create_out_gate | actual_create_in_gate |
//   actual_out_call_gate | actual_in_call_gate |
//   actual_out_reply_gate | actual_in_reply_gate
;


// ----- Instance decomposition

decomposition:
   'decomposed' (substructure_reference)?
;

substructure_reference:
   'as' Name
;


// ----- High-level MSC (HMSC)

hmsc:
   {
     new_hmsc_fun(context);
   }
   (hmsc_body | 'expr' msc_expression)
;

hmsc_statement_without_initial:
   text_definition | final_node | intermediate_node
;

hmsc_body:
   (hmsc_statement_without_initial)* initial_node (hmsc_statement)*
;

hmsc_statement:
   text_definition | node_definition
;

node_definition:
   initial_node | final_node | intermediate_node
;

initial_node:
   'initial' connection_list end
   {
      new_start_node_fun(context);
   }
;

final_node:
   Name
   {
     set_node_name_fun(context, (char*) $Name.text->chars);
   }
   ':' 'final' (connection_list
   {
         bug_report_fun(context, "Warinig 14: HMSC has defined a successor for end node");
   })? end
   {
     new_end_node_fun(context);
   }
;

connection_list:
   'connect' label_list
;

label_list:
   Name
   {
     add_connect_name_fun(context, (char*) ($Name.text->chars));
   }
   (',' label_list)?                          //change * to ?
;

intermediate_node:
   Name
   {
      set_node_name_fun(context, (char*) ($Name.text->chars));
   }
   ':' intermediate_node_type connection_list end
   {
     create_connections_fun(context);
   }
;

intermediate_node_type:
   timeable_node | untimeable_node
;

untimeable_node:
   hmsc_connection_node
   {
     new_connection_node_fun(context);
   }
   | hmsc_condition_node
   {
     new_condition_node_fun(context);
   }
;

msc_expression:
   start {new_start_node_fun(context);}

   (node_expression
   | (Name ':'/* {bug_report_fun(context, "Warning: The file is breaking the ITU-T Z120 standard");}*/)?
     text_definition)*  // add Name ':' out of standart Z120_1999
;

start:
   label_name_list end
;

node_expression:
   Name
   {
     set_node_name_fun(context, (char*) ($Name.text->chars));
   }
   ':' (node 'seq' '('label_name_list')'
   {
     create_connections_fun(context);
   }
   | 'end'
   {
     new_end_node_fun(context);
   }
   ) end
;

label_name_list:
   Name
   {
     add_connect_name_fun(context, (char*) ($Name.text->chars));
   }
   ('alt' label_name_list)?
;

node:
   '(' msc_ref_expr ')' (time_interval)?  { new_reference_node_fun(context); }//reference node
   | par_expression (time_interval)?
   | condition_identification {new_condition_node_fun(context);}
   | 'connect' {new_connection_node_fun(context);}
;

par_expression:
   'expr' msc_expression 'endexpr' ('par' 'expr' msc_expression 'endexpr')*
;

hmsc_connection_node:
   /* empty */
;

hmsc_condition_node:
   condition_identification (shared)?
;

//Peter's reguirements to allow multiple definition of top or bottom time information
timeable_node:
   (hmsc_ref_expr_node { new_reference_node_fun(context); } | hmsc_expression)
   ('time' { set_first_time_rel_kind_fun(context, time_def);} time_dest_list end )?
   ( ('top'{ set_first_time_rel_kind_fun(context, top);} time_dest_list end) |
   ('bottom' { set_first_time_rel_kind_fun(context, bottom);} time_dest_list end) )*
;

hmsc_ref_expr_node:
   'reference' (msc_reference_identification ':')? msc_ref_expr
;

hmsc_expression:
   (hmsc_loop_expr | hmsc_opt_expr | hmsc_alt_expr |
   hmsc_seq_expr | hmsc_par_expr | hmsc_exc_expr)
;

hmsc_loop_expr:
   'loop' (loop_boundary)? 'begin' (inline_expr_identification)? end
   hmsc_body
   'loop' 'end'
;

hmsc_opt_expr:
   'opt' 'begin' (inline_expr_identification)? end
   hmsc_body
   'opt' 'end'
;

hmsc_alt_expr:
   'alt' 'begin' (inline_expr_identification)? end
   hmsc_body
   ('alt' end hmsc_body)*
   'alt' 'end'
;

hmsc_seq_expr:
   'seq' 'begin' (inline_expr_identification)? end
   hmsc_body
   ('seq' end hmsc_body)*
   'seq' 'end'
;

hmsc_par_expr:
   'par' 'begin' (inline_expr_identification)? end
   hmsc_body
   ('par' end hmsc_body)*
   'par' 'end'
;

hmsc_exc_expr:
   'exc' 'begin' (inline_expr_identification)? end
   hmsc_body
   'exc' 'end'
;

// end of file
