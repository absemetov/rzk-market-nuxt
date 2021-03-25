<template>
  <v-app-bar app>
    <v-toolbar-title>
      <NuxtLink v-if="RegExp('rzk.com.ru').test($route.name)" to="/" class="text-decoration-none black--text">RZK Market 2.0</NuxtLink>
      <a v-else href="//rzk.com.ru" class="text-decoration-none black--text">RZK Market 2.0</a>
    </v-toolbar-title>
    <v-toolbar-items>
      <v-btn to="/rzk.com.ru" plain>Home</v-btn>
      <v-btn to="/absemetov.org.ua" plain>About</v-btn>
      <v-btn to="/users" plain>Users</v-btn>
      <v-btn to="/login" plain>Login</v-btn>
    </v-toolbar-items>
  </v-app-bar>
</template>
