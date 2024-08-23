# Estrutura de Dados (C++)

---

Repositório que contém o código das Estruturas de Dados desenvolvidos na disciplina de **GAC108 - DCC/UFLA**.
Todos códigos foram baseados nas aulas e materiais disponibilizados pelos docentes e são de minha autoria.

# Conteúdos

> As estruturas de dados disponibilizadas neste repositório foram todas implementadas utilizando a abstração em TAD's,
> mais especificamente classes. Portanto, caso seja seu primeiro contato com esse paradigma de programação, recomendo
> que comece por [aqui](doc/TAD.md).


> Ao longo da disciplina, para se verificar o aprendizado dos alunos, os diversos conteúdos abordados são aplicados em
> exercícios disponibilizados na plataforma **[Dredd](https://dredd.dac.ufla.br/)**. Você pode conferir uma das
> possíveis soluções para tais exercícios **[aqui](exerciciosDredd)**.

| Estrutura de Dados                          |                                                         Tópicos                                                          |
|:--------------------------------------------|:------------------------------------------------------------------------------------------------------------------------:|
| [Pilhas](src/stack)                         |                   [Pilhas Encadeadas](src/stack/linked)     <br/>[Pilhas em Arrays](src/stack/_array)                    |
| [Filas](src/queue)                          |             [Filas Encadeadas](src/queue/linked/)  <br/>   [Filas em Arrays (Circulares)](src/queue/_array/)             |
| [Heaps](src/heap)                           |    [MaxHeaps](src/heap/maxHeap)   <br/>     [MinHeaps](src/heap/minHeap)   <br/>     [Torneios](src/heap/tournament)     |
| [Listas](src/list)                          |  [Listas Encadeadas](src/list/linked)   <br/>   [Deques]()   <br/>   [Vetores Expansíveis]()  <br/>   [Sequence Set]()   |
| [Tabelas Hash](src/hash)                    |     [Colisão por Encadeamento](src/hash/linked)   <br/>   [Colisão por Endereçamento Aberto](src/hash/open_address)      |
| [Árvores Binárias de Busca](/arvores/abb)   |                     [Árvores Binárias de Busca](/arvores/abb/abb) <br/>  [Tries](arvores/abb/tries)                      |
| [Árvores Balanceadas](/arvores/balanceadas) |                [AVL](/arvores/balanceadas/avl)   <br/>   [Árvores Rubro-Negras](/arvores/balanceadas/rb)                 |
| [Árvores B](/arvores/B)                     | [Árvores 2-3](/)   <br/>    [Árvores 2-3-4](/)  <br/>   [Árvores B](/)  <br/>   [Árvores B+](/)  <br/>   [Árvores B*](/) |

---

## Sobre o repositório

### Estrutura

O repositório consiste em alguns arquivos mui importantes ao funcionamento do que ele se dispõem, eles são:

- [.gitignore](.gitignore), arquivo contendo os arquivos, padrões de arquivos, que devem ser ignorados pelo git, sistema
  de controle de versionamento;
- [.pre-commit-config.yaml](.pre-commit-config.yaml), arquivo contendo as especificações de gatilhos que devem ser
  acionados pelo pre-commit mediante um commit, a fim de manter padrões de estruturação de arquivos e, possivelmente,
  evitar erros passíveis de identificação por ferramentas dedicadas a isso;
- [conanfile.py](conanfile.py), arquivo de configuração do Conan 2. De forma simplificada, o Conan é um gerenciados de
  pacotes para C++, ele permite incluir bibliotecas públicas que não fazem parte da biblioteca padrão do C++;
- Diretório [src](src), este diretório contem as implementações das estruturas de dados que jazem nesse repositório no
  formato de arquivos .cpp;
- Diretório [include](include), diretório que contem os arquivos de cebeçalhos das estruturas de dados do projeto;
- [requirements.txt](requirements.txt), arquivo que contém as bibliotecas requeridas em um ambiente virtual python para
  a manipulação do projeto;
- [meson.build](meson.build), arquivo de configuração na raiz do projeto no que tange ao funcionamento adequado do
  sistema de auxílio à construção do projeto, o meson;
- [exerciciosDredd](exerciciosDredd), diretório contendo a solução de algumas atividades da plataforma Dredd;
- 