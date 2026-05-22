# Clyvo Companion – Monitoramento Preditivo e Adesão Veterinária 🐾
### Sprint 1 - Disruptive Architectures: IoT, IoB & Generative IA

---

## 📋 Sobre o Projeto
O **Clyvo Companion** é uma plataforma focada na continuidade clínica e preventiva para o mercado pet (B2B). O sistema resolve um dos grandes gargalos das clínicas veterinárias: o abandono de tratamentos pós-operatórios e a dificuldade dos tutores em identificar sintomas sutis de complicações.

Esta vertente do ecossistema compreende o **Protótipo de IoT**, desenvolvido para monitorar em tempo real a temperatura corporal de animais em recuperação cirúrgica. Os dados coletados na ponta (Edge) são enviados através de protocolos leves para um broker de mensagens e consolidados em um Dashboard analítico e preditivo local desenvolvido em **Node-RED**, voltado para o corpo médico da clínica veterinária.

---

## 🏗️ Arquitetura do System IoT
O protótipo foi projetado com foco em leveza, escalabilidade e eficiência energética, dividindo-se em três camadas principais:

1. **Edge (Dispositivo IoT):** Simulado através da plataforma **Wokwi**, utiliza um microcontrolador **ESP32** conectado a um sensor de temperatura e umidade **DHT22** (simulando a telemetria clínica do animal).
2. **Broker MQTT (Protocolo de Comunicação):** O ESP32 utiliza a rede Wi-Fi simulada para se conectar ao broker público **HiveMQ** (`broker.hivemq.com`), transmitindo pacotes de dados estruturados através do protocolo MQTT (porta `1883`) sob o tópico exclusivo do projeto.
3. **Application & Dashboard (Node-RED):** Uma instância local do **Node-RED** atua como camada de processamento e interface visual, consumindo as mensagens do broker e exibindo as métricas em tempo real por meio de um componente gráfico analógico (*Gauge*).

---

## 🛠️ Componentes Utilizados (Hardware Simulado)
* **1x ESP32** (Microcontrolador com conectividade Wi-Fi embarcada).
* **1x Sensor DHT22** (Responsável pela leitura precisa da temperatura corporal simulada do pet).
* **Conexões físicas de fiação:**
  * **VCC (Sensor)** ➡️ **3V3 (ESP32)** (Linha de alimentação - Vermelho)
  * **GND (Sensor)** ➡️ **GND (ESP32)** (Linha de aterramento - Preto)
  * **SDA/Data (Sensor)** ➡️ **GPIO 23 (ESP32)** (Linha de dados digitais - Verde)

---

## 🔌 Por que escolher o Protocolo MQTT?
Para o ecossistema do **Clyvo Companion**, o protocolo **MQTT (Message Queuing Telemetry Transport)** foi escolhido em detrimento do HTTP tradicional pelos seguintes motivos:
* **Leveza Extrema:** O cabeçalho de mensagem reduzido consome o mínimo de banda de rede e energia, tornando-se a escolha ideal para dispositivos vestíveis (*wearables*) ou coleiras inteligentes que dependem de bateria.
* **Arquitetura Publish/Subscribe:** Permite o desacoplamento entre o dispositivo físico e a aplicação. O ESP32 apenas publica as informações no tópico, e a clínica (via Node-RED) consome os dados assincronamente.
* **Baixa Latência:** Entrega as atualizações quase instantaneamente, permitindo ações preditivas imediatas caso o animal apresente picos febris.

---

## 🚀 Como Executar o Projeto

### Pré-requisitos
Para reproduzir o ambiente, você precisará de:
1. Uma instalação funcional do **Node-RED** rodando localmente (via Node.js ou Docker).
2. Acesso à internet para carregar o simulador web do Wokwi e conectar ao broker público.

### Passo 1: Configuração no Wokwi
1. Acesse o seu projeto no [Wokwi](https://wokwi.com/).
2. No gerenciador de bibliotecas (**Library Manager**), certifique-se de adicionar as seguintes dependências:
   * `DHT sensor library` (by Adafruit)
   * `Adafruit MQTT Library`
3. Certifique-se de que o código aponta para o servidor público correto:
   ```cpp
   #define MQTT_SERVER      "broker.hivemq.com"
   #define MQTT_SERVERPORT  1883
   #define MQTT_TOPIC       "clyvocompanion/pet/temperatura"

Clique no botão Play para iniciar a simulação do microcontrolador.

Passo 2: Configuração no Node-RED
Abra o Node-RED no seu navegador (geralmente em http://localhost:1880).

Caso ainda não tenha, instale a paleta de gráficos acessando Menu ➡️ Manage palette ➡️ Install e busque por node-red-dashboard.

Arraste um nó mqtt in para o fluxo e configure o servidor como broker.hivemq.com (porta 1883) e o tópico como clyvocompanion/pet/temperatura.

Arraste um nó gauge (da categoria Dashboard), configure uma nova aba/grupo se necessário, ajuste o limite de exibição (Mínimo 35 / Máximo 42) e conecte a saída do nó MQTT à entrada do nó Gauge.

Clique em Deploy no canto superior direito.

Passo 3: Testando a Preditividade do Protótipo
Com a simulação do Wokwi ativa, clique em cima do componente físico DHT22.

Altere o controle deslizante (slider) para simular uma variação de temperatura (ex: mude para 39.2 °C).

Observe o Monitor Serial do Wokwi indicar o envio bem-sucedido dos dados.

Acesse a interface visual do Node-RED através do endereço http://localhost:1880/ui e verifique o ponteiro analógico atualizar o valor automaticamente em tempo real.

### 🧑‍💻 Integrantes do Grupo
Geovanne Coneglian Passos - RM 562673

Lucas Silva Gastão Pinheiro - RM 563960

Guilherme Soares De Almeida - RM 563143
