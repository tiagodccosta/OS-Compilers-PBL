## Utilitários de Linha de Comandos Linux com Analisador léxico e sintático em Lex e Yacc

### Introdução

Este projeto implementa um subconjunto de utilitários comuns de linha de comandos Linux (`ls`, `pwd`, `head`, `tail`, `mkdir`, `rmdir`, `find`) juntamente com um analisador léxico e sintático em LEX e YACC. O projeto demonstra conceitos fundamentais de sistemas operativos e princípios de teoria de compiladores.

### Estrutura do Projeto

```
linux-utils-project/
├── ls/                   # Implementação do comando ls
├── pwd/                  # Implementação do comando pwd
├── head/                 # Implementação do comando head
├── tail/                 # Implementação do comando tail
├── mkdir/                # Implementação do comando mkdir
├── rmdir/                # Implementação do comando rmdir
├── find/                 # Implementação do comando find
├── yacc/                 # Analisador de comandos usando Lex/Yacc
│   ├── command_lexer.l   # Analisador léxico
│   ├── command_parser.y  # Analisador sintático
│   ├── command.h         # Estruturas de dados
│   ├── main.c            # Programa principal
│   └── makefile          # Ficheiro de compilação para o analisador
├── h                     # Script de execução de comandos
└── makefile              # Ficheiro de compilação principal
```

### Implementações de Comandos

1. **ls** - Lista o conteúdo de diretórios com opções:
   - `-a` Mostrar ficheiros ocultos
   - `-l` Usar formato de listagem detalhado
   - `-r` Ordem inversa ao ordenar

2. **pwd** - Mostra o diretório de trabalho atual com opções:
   - `-L` Mostrar diretório de trabalho lógico (seguir ligações simbólicas)
   - `-P` Mostrar diretório físico sem seguir ligações simbólicas
   - `--help` Mostrar informação de ajuda

3. **head** - Exibir a primeira parte dos ficheiros com opções:
   - `-n <num>` Exibir as primeiras \<num\> linhas (padrão: 10)
   - `-c <num>` Exibir os primeiros \<num\> bytes
   - `-q` Nunca mostrar cabeçalhos com nomes de ficheiros

4. **tail** - Exibir a última parte dos ficheiros com opções:
   - `-n <num>` Exibir as últimas \<num\> linhas (padrão: 10)
   - `-f` Seguir o ficheiro à medida que cresce
   - `-q` Nunca mostrar cabeçalhos com nomes de ficheiros

5. **mkdir** - Criar diretórios com opções:
   - `-p` Criar diretórios parentais conforme necessário
   - `-v` Exibir uma mensagem para cada diretório criado
   - `-m <modo>` Definir modo de permissão

6. **rmdir** - Remover diretórios vazios com opções:
   - `-p` Remover também diretórios parentais
   - `-v` Modo detalhado
   - `--ignore-fail-on-non-empty` Ignorar falhas para diretórios não vazios

7. **find** - Procurar ficheiros com opções:
   - `-name <padrão>` Procurar ficheiros com nome específico
   - `-type <tipo>` Procurar tipo específico de ficheiro (f para ficheiro, d para diretório)
   - `-size <tamanho>` Procurar ficheiros de tamanho específico

#### Análise Léxica (command_lexer.l)

O ficheiro Lex define tokens para:
- Nomes de comandos (`ls`, `pwd`, etc.)
- Opções de comandos (`-a`, `-l`, etc.)
- Tipos de argumentos (números, strings)

Lex divide a string do comando de entrada em tokens que podem ser processados pelo analisador. Por exemplo, `ls -a /home` seria tokenizado como `CMD_LS`, `OPT_ALL` e um token `STRING` para `/home`.

#### Análise Gramatical (command_parser.y)

O ficheiro Yacc define a gramática para cada comando, incluindo:
- Sintaxe válida de comandos
- Opções aceitáveis para cada comando
- Padrões e combinações de argumentos

O analisador valida os comandos contra esta gramática e constrói dados estruturados que representam a intenção do utilizador.

#### Estruturas de Dados (command.h)

Uma estrutura `CommandInfo` armazena informação do comando analisado:
- O comando base (ls, pwd, etc.)
- Sinalizadores de opção (ls_all, ls_long, etc.)
- Argumentos adicionais (caminhos de ficheiros, padrões)

#### Execução de Comandos (main.c)

Após a análise, o sistema:
1. Valida o comando analisado
2. Constrói um array de argumentos
3. Executa o binário de comando apropriado usando `execv()`

### Sistema de Compilação

O projeto usa Make para compilação:
1. Cada diretório de comando contém um Makefile para compilar esse utilitário específico
2. O diretório Yacc tem um Makefile para compilar o analisador
3. Um Makefile raiz coordena todo o processo de compilação

### Executor de Comandos (h)

O script `h` serve como ponto de entrada para os utilizadores. Ele:
1. Recebe o comando do utilizador (por exemplo, `./h ls -a`)
2. Passa o comando para o analisador Yacc/Lex
3. O analisador processa o comando e executa o utilitário apropriado

### Processo de Compilação e Execução

Quando um comando é executado através de `./h`:
1. O script chama o analisador com os argumentos do comando
2. Lex tokeniza a entrada
3. Yacc valida os tokens contra a gramática
4. Se válido, o comando apropriado é executado com os argumentos analisados

### Exemplos de Utilização

```bash
# Listar ficheiros no diretório atual
./h ls

# Listar todos os ficheiros, incluindo os ocultos
./h ls -a

# Mostrar formato de listagem detalhado
./h ls -l

# Mostrar diretório de trabalho atual
./h pwd

# Mostrar as primeiras 5 linhas de um ficheiro
./h head -n 5 nome_do_ficheiro.txt

# Encontrar todos os ficheiros C recursivamente
./h find . -name "*.c"
```