# Clyvo Care – Monitoramento Preditivo e Adesão Veterinária 🐾
### Sprint 1 - Disruptive Architectures: IoT, IoB & Generative IA

---

## 📋 Sobre o Projeto
O **Clyvo Care** é uma plataforma focada na continuidade clínica e preventiva para o mercado pet (B2B). O sistema resolve um dos grandes gargalos das clínicas veterinárias: o abandono de tratamentos pós-operatórios e a dificuldade dos tutores em identificar sintomas sutis de complicações.

Esta vertente do ecossistema compreende o **Protótipo de IoT**, desenvolvido para monitorar em tempo real a temperatura corporal de animais em recuperação cirúrgica. Os dados coletados são enviados diretamente para a nuvem através de protocolos IoT e consolidados em um Dashboard analítico e preditivo voltado para o corpo médico da clínica.

---

## 🏗️ Arquitetura do Sistema IoT
O protótipo foi projetado com foco em leveza, escalabilidade e eficiência energética, dividindo-se em três camadas principais:

1. **Edge (Dispositivo IoT):** Simulado através da plataforma **Wokwi**, utiliza um microcontrolador **ESP32** conectado a um sensor de temperatura e umidade **DHT22** (simulando o monitoramento clínico do animal).
2. **Broker MQTT (Protocolo de Comunicação):** O ESP32 utiliza a rede Wi-Fi para se conectar ao broker MQTT do **Adafruit IO**, transmitindo pacotes de dados estruturados através do protocolo MQTT (porta `1883`).
3. **Application & Cloud (Dashboard):** A plataforma **Adafruit IO** atua como camada de ingestão e visualização de dados, disponibilizando gráficos de linha históricos e medidores analógicos de status imediato (*Gauges*).

---

## 🛠️ Componentes Utilizados (Hardware Simulado)
* **1x ESP32** (Microcontrolador com conectividade Wi-Fi embarcada).
* **1x Sensor DHT22** (Responsável pela leitura precisa da temperatura ambiente/corporal simulada).
* **Conexões físicas de fiação:**
  * **VCC (Sensor)** ➡️ **3V3 (ESP32)** (Linha de alimentação - Vermelho)
  * **GND (Sensor)** ➡️ **GND (ESP32)** (Linha de aterramento - Preto)
  * **SDA/Data (Sensor)** ➡️ **GPIO 23 (ESP32)** (Linha de dados digitais - Verde)

---

## 🔌 Por que escolhemos o Protocolo MQTT?
Para o projeto Clyvo Care, o protocolo **MQTT (Message Queuing Telemetry Transport)** foi escolhido em detrimento do HTTP tradicional pelos seguintes motivos:
* **Leveza Extrema:** O MQTT consome muito menos dados e energia, ideal para dispositivos vestíveis (*wearables*) ou coleiras inteligentes que monitoram pets continuamente por bateria.
* **Arquitetura Publish/Subscribe:** Permite uma comunicação assíncrona onde o dispositivo apenas publica os dados no *feed*, e múltiplos painéis ou relatórios da clínica veterinária podem assinar e receber as atualizações de forma instantânea.
* **Baixa Latência:** Entrega atualizações em tempo real (como demonstrado na atualização instantânea dos ponteiros do Dashboard).

---

## 🚀 Como Executar o Projeto

### Pró-requisitos
Para reproduzir o ambiente, você precisará de:
1. Uma conta gratuita no [Adafruit IO](https://io.adafruit.com/).
2. Acesso à internet para rodar o simulador web do Wokwi.

### Passo 1: Configuração no Adafruit IO
1. Faça login no Adafruit IO.
2. Acesse a aba **Feeds** e clique em **New Feed**. Crie um feed chamado exatamente `temperatura`.
3. Acesse a aba **Dashboards**, clique em **New Dashboard** e atribua o nome `Clyvo Care - Painel da Clinica`.
4. Dentro do Dashboard, clique na engrenagem ➡️ **Create New Block**:
   * Adicione um bloco do tipo **Gauge** associado ao feed `temperatura` (Limites recomendados: Min `35` / Max `42`).
   * Adicione um bloco do tipo **Line Chart** associado ao feed `temperatura` para exibir o histórico de leituras.
5. No menu superior direito, clique na chave dourada (**Adafruit IO Key**) e copie o seu `Username` e a sua `Active Key`.

### Passo 2: Configuração no Wokwi
1. Acesse o seu projeto no [Wokwi](https://wokwi.com/).
2. No gerenciador de bibliotecas (**Library Manager**), certifique-se de ter adicionado:
   * `DHT sensor library` (by Adafruit)
   * `Adafruit MQTT Library`
3. No arquivo principal `sketch.ino`, localize as diretivas de configuração e insira as suas credenciais obtidas no Passo 1:

Clique no botão Play para iniciar a simulação.

### Passo 3: Testando a Preditividade da IA/IoT
Com a simulação rodando, clique em cima do componente físico DHT22 no Wokwi.

Altere o slider de temperatura manualmente (Ex: arraste para 39.5 °C ou mais).

Monitore o Serial Monitor do Wokwi: o sistema capturará a alteração e enviará com sucesso via MQTT.

Volte para a aba do Adafruit IO e observe o ponteiro do velocímetro e a linha do gráfico se moverem sozinhos em tempo real.

### 🧑‍💻 Integrantes do Grupo
Geovanne Coneglian Passos- RM 562673

Lucas Silva Gastão Pinheiro - RM 563960

Guilherme Soares De Almeida - RM 563143
   ```cpp
   #define AIO_USERNAME    "SEU_USER_AQUI" 
   #define AIO_KEY         "SUA_KEY_AQUI"
