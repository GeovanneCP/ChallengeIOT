# Clyvo Companion – Monitoramento Preditivo e Adesão Veterinária 🐾
### 1ª Sprint - Disruptive Architectures: IoT, IoB & Generative IA

---

## 📋 Sobre o Projeto
O **Clyvo Companion** é uma plataforma B2B desenhada para clínicas veterinárias com foco em continuidade clínica e medicina preventiva. A solução ataca diretamente o problema do abandono de tratamentos pós-operatórios e a dificuldade de tutores em identificar sintomas sutis de complicações em animais de estimação.

Este repositório contém o **Protótipo Funcional de IoT** desenvolvido nesta sprint. Ele simula o monitoramento telemétrico contínuo da temperatura corporal de um pet em recuperação cirúrgica, transportando os dados em tempo real até um painel centralizado em ambiente clínico.

---

## 🏗️ Arquitetura e Tecnologias Utilizadas
O ecossistema foi projetado seguindo as melhores práticas de IoT e IoB (Internet of Bodies), dividindo-se em três camadas estruturais:

[ ESP32 + DHT22 ] --(Wi-Fi / MQTT)--> [ Broker HiveMQ ] --> [ Node-RED Dashboard ]

* **Edge Computing (Dispositivo IoT):** Microcontrolador **ESP32** integrado a um sensor digital **DHT22** (Temperatura/Umidade), programado em C++ através da IDEs padrão do ecossistema Arduino.
* **Camada de Transporte (Protocolo MQTT):** Comunicação realizada via protocolo **MQTT (Message Queuing Telemetry Transport)** intermediada pelo broker público **HiveMQ** (`broker.hivemq.com:1883`).
* **Application Layer (Dashboard):** Servidor local de fluxo de dados **Node-RED** utilizando a biblioteca nativa de componentes visuais `node-red-dashboard`.

### 🔌 Justificativa do Protocolo MQTT
Optou-se pelo uso do protocolo MQTT em detrimento do HTTP pelos seguintes fatores técnicos:
1. **Baixo Overhead de Rede:** O cabeçalho leve consome o mínimo de pacotes de dados, ideal para dispositivos veterinários compactos móveis que operam por bateria.
2. **Modelo Publish/Subscribe:** Desacopla o hardware da aplicação, permitindo atualizações assíncronas em tempo real com latência quase nula.

---

## 📂 Estrutura do Repositório
* `/src` ou `sketch.ino`: Código-fonte em C++ pronto para o microcontrolador ESP32.
* `diagram.json`: Arquivo de mapeamento de conexões físicas para importação no simulador.
* `flows.json`: Arquivo de exportação do fluxo do Node-RED para reconstrução imediata do dashboard.

---

## 🚀 Instruções de Uso

### 1. Executando o Hardware no Wokwi
1. Abra o arquivo `sketch.ino` contido neste repositório e copie o código-fonte.
2. Acesse o seu simulador [Wokwi](https://wokwi.com/), inicie um projeto **ESP32** limpo e cole o código na aba correspondente.
3. Certifique-se de instalar as dependências `DHT sensor library` e `Adafruit MQTT Library` no **Library Manager** do simulador.
4. Monte as conexões conforme o arquivo `diagram.json` ou siga o pinout básico:
   * **VCC (Sensor)** ➡️ **3V3 (ESP32)**
   * **GND (Sensor)** ➡️ **GND (ESP32)**
   * **SDA/Data (Sensor)** ➡️ **GPIO 23 (ESP32)**
5. Clique no botão **Play** para iniciar a transmissão.

### 2. Executando o Dashboard no Node-RED
1. Certifique-se de que o Node-RED está rodando em sua máquina (`http://localhost:1880`).
2. Acesse o **Menu Superior Direito ➡️ Import** e selecione o arquivo `flows.json` disponível neste repositório.
3. Clique em **Deploy** no canto superior direito.
4. Acesse a interface do painel do usuário final através do endereço do navegador:
   👉 `http://localhost:1880/ui`

---

## 📈 Resultados Parciais (Prova de Conceito)
Nesta primeira etapa da entrega, os seguintes objetivos técnicos foram plenamente atingidos e validados:
* **Conectividade Eficiente:** O firmware embarcado conecta com sucesso à rede Wi-Fi simulada e realiza o handshake com o broker MQTT de forma estável.
* **Telemetria em Tempo Real:** Alterações manuais de temperatura simuladas no sensor DHT22 geram gatilhos imediatos de publicação (*publish*) no tópico do projeto (`clyvocompanion/pet/temperatura`).
* **Ingestão e Exibição Fluida:** O Node-RED atua consumindo os dados diretamente do broker, renderizando o ponteiro analógico do *Gauge* em tempo real sem necessidade de requisições ativas (*polling*) ou atualizações de página.

---

## 🧑‍💻 Integrantes do Grupo
* **Geovanne Coneglian Passos** - RM 562673
* **Lucas Silva Gastão Pinheiro** - RM 563960
* **Guilherme Soares De Almeida** - RM 563143
