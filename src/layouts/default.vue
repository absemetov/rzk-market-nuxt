<template>
  <v-app>
    <v-app-bar app>
      <v-toolbar-title>
        <NuxtLink v-if="RegExp('rzk.com.ru').test($route.name)" to="/" class="text-decoration-none black--text">RZK Market 2.0 nuxt-link</NuxtLink>
        <a v-else href="//rzk.com.ru" class="text-decoration-none black--text">RZK Market 2.0</a>
      </v-toolbar-title>
    </v-app-bar>
    <v-main>
      <v-container>
        <nuxt/>
      </v-container>
    </v-main>
    <v-footer app>
      <a href="//absemetov.org.ua">absemetov.org.ua</a>
    </v-footer>
  </v-app>
</template>

<script>
  export default {

  }
</script>
