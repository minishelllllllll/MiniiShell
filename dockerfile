FROM ubuntu:latest

# Install necessary packages
RUN apt-get update && \
    apt-get install -y make gcc libreadline-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /minishell

# Copy all files to the container
COPY . .

# Make the test script executable
RUN chmod +x test.sh

# Set the default command
CMD ["sh", "-c", "./test.sh"]
