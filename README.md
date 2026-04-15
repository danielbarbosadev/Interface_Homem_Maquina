# Interface Homem-Máquina (IHM) para Controle de Iluminação

🔗 **Simulação no Tinkercad:** [Projeto Tinkercad](https://www.tinkercad.com/things/44HjNojgNfQ-ihm-300326)

Este projeto é um protótipo funcional de um painel de controle de iluminação com ajuste de intensidade desenvolvido no Tinkercad. Ele utiliza uma interface de navegação por menu em um display LCD I2C para gerenciar dois canais independentes de saída, permitindo o controle total de ligar/desligar e a graduação precisa de brilho através de comandos digitais.
O diferencial deste sistema é a IHM (Interface Homem-Máquina) intuitiva, que utiliza um cursor visual para selecionar qual dispositivo configurar, simulando o funcionamento de controladores residenciais modernos e sistemas de automação de estúdio.

## 🚀 Funcionalidades
**Interface Homem-Máquina (IHM):** Menu interativo no display LCD 16x2 que indica qual canal está selecionado através de um seletor visual (>).

**Controle de Intensidade PWM:** Ajuste de brilho em 10 níveis para cada LED, utilizando modulação por largura de pulso para economia de energia e suavidade.

**Seleção Independente:** Navegação vertical (Botões UP/DOWN) para alternar entre os canais LED A e LED B sem interferir no estado do outro.

Controle de Estado: Botão SELECT dedicado para alternar entre os estados ON (Ligado) e OFF (Desligado) de forma instantânea.

Feedback de Dados: Exibição em tempo real da porcentagem de potência aplicada (0% a 100%) ou indicação de "OFF" diretamente no visor.

## 📝 Como funciona o Código?

O software foi projetado seguindo o conceito de máquina de estados simples:

**Varredura:** O sistema lê constantemente os 5 botões, detectando apenas o momento em que são pressionados (borda de descida).

**Lógica de Navegação:** Os botões UP e DOWN movem a seta do menu, enquanto LEFT e RIGHT alteram os valores internos de intensidade.

**Atualização Inteligente:** O LCD e as saídas PWM só são atualizados quando ocorre uma mudança de estado (atualizaSaidas), evitando oscilações desnecessárias no processamento e no display.


## 🛠️ Tecnologias Utilizadas

**C++ (Arduino SDK):** Lógica de programação estruturada com uso de variáveis static para otimização de memória e controle de estado dos botões.

**Protocolo I2C:** Comunicação eficiente com o display LCD utilizando apenas dois pinos (SDA/SCL), economizando portas do microcontrolador.

**Componentes de Hardware:**

**LEDs & Resistores:** Atuadores de saída configurados para responder a sinais analógicos simulados.

**Push-buttons:** Conjunto de 5 botões configurados com INPUT_PULLUP interno, eliminando a necessidade de resistores externos.

**Display LCD 16x2:** Monitoramento visual de todas as operações do sistema.

**Tinkercad:** Ambiente de simulação para validação da eletrônica e depuração do código.


