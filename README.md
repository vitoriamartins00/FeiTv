# FEItv

A FEItv é um projeto acadêmico desenvolvido em linguagem C, como objetivo de simular algumas funcionalidades de uma plataforma de vídeos por meio de menus no terminal.

O programa permite cadastrar usuario, realizar login, pesquisar vídeos, curtir ou descurtir conteúdos e organizar uma lista de favoritos. As informações são armazenadas em arquivos de texto.

## Funcionalidades

- Cadastro e login de usuários.
- Busca de vídeos no catálogo.
- Registro e remoção de curtidas.
- Criação e gerenciamento de favoritos.
- Consulta, adição e remoção de vídeos da lista de favoritos.
- Navegação por menus no terminal.

## Linguagem e recursos utilizados

- Linguagem C.
- Bibliotecas padrão da linguagem, como `stdio.h` e `string.h`.
- Arquivos `.txt` para armazenamento dos dados.
- Visual Studio Code para edição e execução do projeto.

## Organização dos arquivos

| Arquivo | Função |
|---|---|
| `main.c` | Menu inicial e controle das opções principais. |
| `usuarios.c` | Cadastro e autenticação dos usuários. |
| `home.c` | Menu apresentado após o login. |
| `videos.c` | Busca de vídeos e controle de curtidas. |
| `favoritos.c` | Gerenciamento da lista de favoritos. |
| `entidades.h` | Estruturas de dados e declarações das funções. |
| `videos.txt` | Catálogo de vídeos utilizado pelo programa. |
| `usuarios.txt` | Dados dos usuários cadastrados durante a execução. |
| `curtidas.txt` | Registros de curtidas. |

## Como executar

É necessário ter um compilador C, como o GCC, instalado no computador.

1. Abra o terminal na pasta principal do projeto.
2. Compile os arquivos:

   ```bash
   gcc main.c home.c usuarios.c videos.c favoritos.c -o feitv
   ```

3. Execute o programa no macOS ou Linux:

   ```bash
   ./feitv
   ```

O arquivo `videos.txt` deve permanecer na pasta de onde o programa é executado, pois o código utiliza caminhos relativos para acessar os dados. Os arquivos `usuarios.txt` e `curtidas.txt` são utilizados para registrar informações durante o uso.

## Observações

Este projeto foi desenvolvido para fins acadêmicos e utiliza arquivos de texto como forma de persistência. O cadastro atual grava senhas em texto simples, portanto não deve ser utilizado com senhas reais ou dados sensíveis, nem como sistema de autenticação em produção.

## Contexto

Projeto desenvolvido durante o semestre para praticar programação estruturada em C, uso de funções, estruturas (`struct`), manipulação de arquivos e organização do código em diferentes módulos.
